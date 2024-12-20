/* vfork_fd_test.c

   Демонстрация того, что vfork() создает для дочернего процесса отдельный набор файловых дескрипторов,
   которые не влияют на родительский процесс.
*/

#define _BSD_SOURCE     /* Чтобы получить объявление vfork() из <unistd.h>
                           в случае, если _XOPEN_SOURCE >= 700 */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    // Создаем дочерний процесс с помощью vfork()
    switch (vfork()) {
    case -1: 
        errExit("vfork"); // Если произошла ошибка при вызове vfork, выводим сообщение и завершаем программу

    case 0: 
        // В дочернем процессе закрываем дескриптор стандартного вывода
        if (close(STDOUT_FILENO) == -1)
            errMsg("close - child"); // Сообщение об ошибке, если не удается закрыть дескриптор
        _exit(EXIT_SUCCESS); // Завершаем дочерний процесс

    default: 
        break; // Родительский процесс продолжает выполнение
    }

    /* Родительский процесс дважды пытается закрыть STDOUT_FILENO.
       Только вторая попытка должна завершиться неудачей, что подтверждает,
       что закрытие STDOUT_FILENO в дочернем процессе не повлияло на родителя. */

    if (close(STDOUT_FILENO) == -1)
        errMsg("close"); // Сообщение об ошибке при первой попытке закрытия дескриптора
    if (close(STDOUT_FILENO) == -1)
        errMsg("close"); // Сообщение об ошибке при второй попытке закрытия дескриптора

    exit(EXIT_SUCCESS); // Завершаем родительский процесс
}
/*
### Резюме кода
Данный код демонстрирует, что дочерний процесс, созданный с помощью `vfork()`, имеет независимый набор файловых дескрипторов от родительского процесса. 
В коде сначала закрывается стандартный вывод (STDOUT_FILENO) в дочернем процессе, а затем родительский процесс пытается дважды закрыть тот же дескриптор. 
Вторая попытка завершается неудачей, показывая, что закрытие в дочернем процессе не повлияло на родителя.
*/
