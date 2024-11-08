/* mix23_linebuff.c

   Демонстрирует влияние буферизации stdio при использовании функций библиотеки
   stdio и системных вызовов ввода-вывода для работы с одним и тем же файлом.
   Наблюдайте разницу в выводе при запуске этой программы с выводом в терминал
   и при перенаправлении вывода в файл.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("If I had more time, \n");  // Запись в буфер stdio
    write(STDOUT_FILENO, "I would have written you a shorter letter.\n", 43); // Прямой системный вызов write()
    exit(EXIT_SUCCESS);
}

/*
Пояснение:
printf записывает данные в буфер, и при выводе на терминал буфер может очищаться строка за строкой (линейно), 
но при выводе в файл буфер может записаться только после завершения программы. 
Однако вызов write сразу записывает данные, минуя буфер stdio.

*/