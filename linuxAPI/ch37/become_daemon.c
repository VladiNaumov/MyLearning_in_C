/* become_daemon.c

   Реализация функции, которая инкапсулирует шаги, необходимые для перевода процесса в режим демона.
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "become_daemon.h"
#include "tlpi_hdr.h"

/**
 * Преобразует текущий процесс в демон.
 *
 * Аргументы:
 * - flags: Флаги, определяющие поведение (например, не менять текущий каталог
 *   или не закрывать открытые файловые дескрипторы).
 *
 * Возвращает:
 * - 0 в случае успеха.
 * - -1 при ошибке.
 */
int becomeDaemon(int flags) {
    int maxfd, fd;

    /* Первый fork: становится фоновым процессом */
    switch (fork()) {
    case -1: return -1;                 /* Ошибка */
    case 0:  break;                     /* Потомок продолжает выполнение */
    default: _exit(EXIT_SUCCESS);       /* Родитель завершает работу */
    }

    /* Создать новую сессию, чтобы стать лидером */
    if (setsid() == -1)
        return -1;

    /* Второй fork: гарантирует, что процесс не станет лидером сессии */
    switch (fork()) {
    case -1: return -1;                 /* Ошибка */
    case 0:  break;                     /* Потомок продолжает выполнение */
    default: _exit(EXIT_SUCCESS);       /* Родитель завершает работу */
    }

    /* Установка режима доступа к файлам (если не указан флаг BD_NO_UMASK0) */
    if (!(flags & BD_NO_UMASK0))
        umask(0);

    /* Переход в корневой каталог (если не указан флаг BD_NO_CHDIR) */
    if (!(flags & BD_NO_CHDIR))
        chdir("/");

    /* Закрытие всех открытых файлов (если не указан флаг BD_NO_CLOSE_FILES) */
    if (!(flags & BD_NO_CLOSE_FILES)) {
        maxfd = sysconf(_SC_OPEN_MAX);
        if (maxfd == -1)                /* Если лимит не определён... */
            maxfd = BD_MAX_CLOSE;       /* использовать значение по умолчанию */

        for (fd = 0; fd < maxfd; fd++)
            close(fd);
    }

    /* Перенаправление стандартных потоков ввода/вывода/ошибок в /dev/null */
    if (!(flags & BD_NO_REOPEN_STD_FDS)) {
        close(STDIN_FILENO);

        fd = open("/dev/null", O_RDWR);
        if (fd != STDIN_FILENO)         /* Убедиться, что 'fd' равен 0 */
            return -1;
        if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
            return -1;
        if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
            return -1;
    }

    return 0; /* Успешное завершение */
}

/*
Резюме:
Эта функция выполняет шаги, необходимые для перевода процесса в демон:
1. Выполняет два вызова fork(), чтобы процесс работал в фоновом режиме и не был лидером сессии.
2. Устанавливает umask(0) для обеспечения полного контроля над правами доступа.
3. Перенаправляет стандартные файловые дескрипторы (stdin, stdout, stderr) в /dev/null.
4. Закрывает все открытые файловые дескрипторы.
5. По желанию изменяет текущий рабочий каталог на корневой.
Функция управляется флагами, которые позволяют включать или отключать определённые действия.
*/
