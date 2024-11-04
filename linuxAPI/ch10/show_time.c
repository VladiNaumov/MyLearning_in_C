/* Этот код демонстрирует влияние локали и временной зоны на функции, работающие с временем. 
Программа отображает текущее время с использованием разных функций, таких как `ctime()`, `asctime()` и `strftime()`, 
которые форматируют вывод времени в зависимости от настроек локали и временной зоны.*/


/* show_time.c

   Короткая программа, показывающая влияние локали и временной зоны на функции работы со временем.

   Запустите программу с такими командами:

        ./show_time
        TZ=":Pacific/Auckland" ./show_time
        TZ=":US/Central" ./show_time
        TZ=":CET" ./show_time
*/

#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

int main(int argc, char *argv[])
{
    time_t t;
    struct tm *loc;
    char buf[BUF_SIZE];

    // Устанавливаем настройки локали для правильного отображения дат
    if (setlocale(LC_ALL, "") == NULL)
        errExit("setlocale");   // Ошибка, если локаль не установилась

    // Получаем текущее время
    t = time(NULL);

    // Выводим время в формате ctime
    printf("ctime() of time() value is:  %s", ctime(&t));

    // Преобразуем время в локальное представление
    loc = localtime(&t);
    if (loc == NULL)
        errExit("localtime");

    // Выводим локальное время с помощью asctime
    printf("asctime() of local time is:  %s", asctime(loc));

    // Форматируем и выводим локальное время с помощью strftime
    if (strftime(buf, BUF_SIZE, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
        fatal("strftime returned 0");
    printf("strftime() of local time is: %s\n", buf);

    exit(EXIT_SUCCESS);
}

/*

### Пояснение
1. **setlocale(LC_ALL, "")**: Устанавливает локальные настройки, основанные на окружении, чтобы функции, работающие со временем, отображали время в формате, характерном для локали пользователя (например, на национальном языке).
  
2. **ctime()**: Преобразует значение времени `time_t` в строку, представляющую дату и время в фиксированном формате (например, "Tue Oct 31 13:59:59 2023\n").

3. **localtime()**: Преобразует время в локальное представление (с учетом временной зоны) и заполняет структуру `tm`, содержащую компоненты даты и времени (год, месяц, день, часы, минуты и т.д.).

4. **asctime()**: Форматирует структуру `tm` в строку в формате, подобном `ctime()`.

5. **strftime()**: Преобразует дату и время в строку, используя указанный формат (`"%A, %d %B %Y, %H:%M:%S %Z"`), где:
   - `%A` — полное название дня недели,
   - `%d` — день месяца,
   - `%B` — полное название месяца,
   - `%Y` — год,
   - `%H:%M:%S` — время (часы, минуты, секунды),
   - `%Z` — временная зона.

Программа полезна для демонстрации того, как локаль и временная зона влияют на формат вывода времени. 
Запуск программы с переменной окружения `TZ` позволяет тестировать различные временные зоны, как указано в примере (например, `TZ=":US/Central"`).
*/