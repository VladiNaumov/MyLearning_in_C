/* envargs.c

   Отображение списка аргументов и переменных окружения.
*/
#include "tlpi_hdr.h"

extern char **environ;  /* Указатель на массив переменных окружения */

int
main(int argc, char *argv[])
{
    int j;
    char **ep;

    /* Отображение списка аргументов командной строки */

    for (j = 0; j < argc; j++)
        printf("argv[%d] = %s\n", j, argv[j]);

    /* Отображение списка переменных окружения */

    for (ep = environ; *ep != NULL; ep++)
        printf("environ: %s\n", *ep);

    exit(EXIT_SUCCESS);  /* Завершение программы с успешным статусом */
}
/*

### Резюме кода

Этот код выводит на экран список аргументов командной строки и список переменных окружения текущего процесса. 
Сначала программа проходит по массиву `argv[]`, отображая переданные аргументы, затем выводит каждую переменную окружения из массива `environ`.
*/