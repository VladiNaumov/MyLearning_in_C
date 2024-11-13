/* t_unlink.c

   Демонстрирует, что при удалении файла он фактически не удаляется из
   файловой системы до тех пор, пока все открытые дескрипторы, ссылающиеся
   на него, не будут закрыты.

   Использование: t_unlink файл
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fd, j, numBlocks;
    char shellCmd[CMD_SIZE];            /* Команда для передачи в system() */
    char buf[BUF_SIZE];                 /* Массив случайных байтов для записи */

    // Проверка аргументов командной строки
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks] \n", argv[0]);

    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks")
                           : 100000;

    /* O_EXCL для гарантии создания нового файла */
    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    // Удаляем имя файла, но дескриптор остаётся открытым
    if (unlink(argv[1]) == -1)
        errExit("unlink");

    // Записываем данные в файл
    for (j = 0; j < numBlocks; j++)
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("partial/failed write");

    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shellCmd);  /* Отображение используемого дискового пространства */

    // Закрываем дескриптор файла, после чего файл будет окончательно удалён
    if (close(fd) == -1)
        errExit("close");
    printf("********** Закрыт дескриптор файла\n");

    /* См. исправление для страницы 348 на http://man7.org/tlpi/errata/.
       В зависимости от различных факторов, таких как случайное планирование
       и размер созданного файла, команда 'df', вызванная ниже, может не
       показать изменения в потребляемом дисковом пространстве, так как
       блоки закрытого файла еще не освобождены ядром. Если это случится,
       добавьте sleep(1) перед вторым вызовом 'df' для гарантии освобождения.
    */

    system(shellCmd);  /* Повторная проверка использования дискового пространства */
    exit(EXIT_SUCCESS);
}
/*

### Описание кода

1. **open()** — Открывает файл с флагом `O_EXCL`, чтобы убедиться, что создаётся новый файл. Дескриптор открывается для записи.
2. **unlink()** — Удаляет имя файла из файловой системы, но так как дескриптор всё ещё открыт, файл будет удалён окончательно только после вызова `close()`.
3. **write()** — Записывает данные в файл.
4. **system()** — Выполняет команду `df`, чтобы показать использование дискового пространства.
5. **close()** — Закрывает дескриптор файла, после чего файл окончательно удаляется и его блоки освобождаются.

Этот код иллюстрирует, что удаление файла не сразу освобождает его блоки в файловой системе, если дескрипторы, ссылающиеся на него, остаются открытыми.
*/