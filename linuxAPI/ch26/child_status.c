/* child_status.c

   Демонстрация использования wait() и макросов W* для анализа статуса дочернего
   процесса, возвращенного функцией wait().

   Использование: child_status [exit-status]

   Если передан аргумент "exit-status", то дочерний процесс немедленно завершается с этим
   статусом. Если аргумент не передан, то дочерний процесс находится в режиме ожидания,
   реагируя на сигналы, которые либо останавливают, либо завершают его - оба состояния
   могут быть обнаружены и различены родительским процессом. Родительский процесс
   многократно ожидает изменения состояния дочернего процесса, пока не обнаружит, что
   процесс либо завершился, либо был убит сигналом.
*/

#include <sys/wait.h>
#include "print_wait_status.h"          /* Объявление printWaitStatus() */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int status;         /* Переменная для хранения статуса завершения дочернего процесса */
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [exit-status]\n", argv[0]);

    switch (fork()) {
    case -1: errExit("fork");           /* Ошибка создания дочернего процесса */

    case 0:             /* Дочерний процесс: завершение с переданным статусом или ожидание сигналов */
        printf("Child started with PID = %ld\n", (long) getpid());
        if (argc > 1)                   /* Статус передан в командной строке? */
            exit(getInt(argv[1], 0, "exit-status"));
        else                            /* Иначе ждет сигналы */
            for (;;)
                pause();                /* Ожидание сигналов */
        exit(EXIT_FAILURE);             /* Невыполнимо, но хорошая практика */

    default:            /* Родительский процесс: многократно ждет, пока дочерний
                           процесс не завершится или не будет убит сигналом */
        for (;;) {
            /* Ожидание состояния дочернего процесса */
            childPid = waitpid(-1, &status, WUNTRACED
#ifdef WCONTINUED       /* Поддержка для возобновленных процессов в некоторых версиях Linux */
                                                | WCONTINUED
#endif
                    );
            if (childPid == -1)
                errExit("waitpid");

            /* Выводит статус в 16-ричном формате и как отдельные десятичные байты */
            printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
                    (long) childPid,
                    (unsigned int) status, status >> 8, status & 0xff);
            printWaitStatus(NULL, status); /* Вывод детализированного статуса */

            /* Завершение родительского процесса, если дочерний завершился или был убит */
            if (WIFEXITED(status) || WIFSIGNALED(status))
                exit(EXIT_SUCCESS);
        }
    }
}
/*

### Резюме кода

Эта программа создает дочерний процесс и анализирует его статус завершения. 
Дочерний процесс либо немедленно завершается с переданным статусом, либо ждет сигналов, которые могут остановить или завершить его. 
Родительский процесс, используя `waitpid()`, отслеживает статус дочернего процесса и выводит его в 16-ричном и десятичном формате. 
Он также использует функцию `printWaitStatus()` для подробного анализа. 
Родительский процесс продолжает ожидание, пока не обнаружит, что дочерний процесс завершился или был убит, после чего завершает свою работу.
*/