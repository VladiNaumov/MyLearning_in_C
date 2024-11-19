/* multi_wait.c

   Демонстрация использования wait(2): создание нескольких дочерних процессов и ожидание их завершения.

   Использование: multi_wait sleep-time...

   Для каждого аргумента командной строки создается дочерний процесс. Каждый дочерний процесс
   засыпает на количество секунд, указанное в соответствующем аргументе командной строки, после чего завершает работу.
   После того как все дочерние процессы будут созданы, родительский процесс многократно вызывает wait(), чтобы
   ожидать завершения всех дочерних процессов и выводить их PID.
*/

#include <sys/wait.h>
#include <time.h>
#include "curr_time.h"              /* Объявление функции currTime() для получения текущего времени */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int numDead;       /* Количество дочерних процессов, для которых уже был вызван wait() */
    pid_t childPid;    /* PID дочернего процесса, для которого был вызван wait() */
    int j;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL);           /* Отключение буферизации стандартного вывода */

    for (j = 1; j < argc; j++) {    /* Создаем один дочерний процесс для каждого аргумента */
        switch (fork()) {
        case -1:
            errExit("fork");        /* Ошибка при создании дочернего процесса */

        case 0:                     /* Дочерний процесс: засыпает и затем завершает работу */
            printf("[%s] child %d started with PID %ld, sleeping %s "
                    "seconds\n", currTime("%T"), j, (long) getpid(),
                    argv[j]);
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));   /* Дочерний процесс засыпает */
            _exit(EXIT_SUCCESS);  /* Завершаем дочерний процесс */

        default:                    /* Родительский процесс продолжает создавать дочерних */
            break;
        }
    }

    numDead = 0;
    for (;;) {                      /* Родительский процесс ждет завершения каждого дочернего процесса */
        childPid = wait(NULL);       /* Ожидает завершения любого дочернего процесса */
        if (childPid == -1) {
            if (errno == ECHILD) {
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);  /* Если больше нет дочерних процессов, завершить программу */
            } else {                /* Неожиданная ошибка при ожидании */
                errExit("wait");
            }
        }

        numDead++;  /* Увеличиваем счетчик завершенных дочерних процессов */
        printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
                currTime("%T"), (long) childPid, numDead);
    }
}
/*

### Резюме кода

Программа создает несколько дочерних процессов, каждый из которых засыпает на определенное количество секунд, указанное в аргументах командной строки. 
Родительский процесс запускает дочерние процессы в цикле и затем использует `wait()` для ожидания завершения каждого дочернего процесса. 
После завершения каждого дочернего процесса родительский процесс выводит его PID и общее количество завершенных процессов.

Если все дочерние процессы завершены, родительский процесс завершает выполнение, выводя сообщение о завершении.

*/