```c
/* Вспомогательная программа для главы 37 */

/* test_become_daemon.c

   Тестируем нашу функцию becomeDaemon().
*/

#include "become_daemon.h" // Заголовочный файл с функцией создания демона
#include "tlpi_hdr.h"      // Общие вспомогательные заголовочные файлы

/**
 * Основная функция программы.
 *
 * Функция вызывает becomeDaemon(), чтобы сделать процесс демоном, 
 * а затем "засыпает" на заданное время. Если время не указано, 
 * используется значение по умолчанию — 20 секунд.
 *
 * Параметры:
 * - argc: Количество аргументов командной строки.
 * - argv: Массив строковых аргументов.
 *
 * Возвращает:
 * - EXIT_SUCCESS (0) — программа завершилась успешно.
 */
int main(int argc, char *argv[]) {
    // Становимся демоном
    becomeDaemon(0);

    /* Обычно демон работает бесконечно; 
       здесь процесс просто спит некоторое время. */

    sleep((argc > 1) ? getInt(argv[1], GN_GT_0, "sleep-time") : 20);

    exit(EXIT_SUCCESS);
}

/*
Резюме кода:
Этот файл представляет собой тестовую программу для проверки функции `becomeDaemon()`. 
Эта функция переводит процесс в режим демона, отделяя его от управляющего терминала 
и выполняя необходимые настройки. После этого процесс "засыпает" на указанное время. 
Если аргумент времени сна не задан, используется значение по умолчанию (20 секунд). 
Программа демонстрирует основные шаги, необходимые для превращения программы в демона.
*/
```