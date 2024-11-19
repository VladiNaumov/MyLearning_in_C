/* prod_no_condvar.c

   Простой пример "производитель-потребитель" с использованием POSIX-потоков,
   в котором не используется условная переменная.

   Вместо этого используется подход "опроса" для проверки доступности ресурсов.

   
*/

#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "tlpi_hdr.h"

/* Мьютекс для защиты общего ресурса (avail) */
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/* Переменная, представляющая количество доступных ресурсов */
static int avail = 0;

/* Поток-производитель */
static void *
producer(void *arg)
{
    int cnt = atoi((char *) arg); // Количество ресурсов, которые нужно произвести

    for (int j = 0; j < cnt; j++) {
        sleep(1); // Симуляция времени производства ресурса

        /* Код производства ресурса пропущен */

        int s = pthread_mutex_lock(&mtx); // Захват мьютекса
        if (s != 0)
            errExitEN(s, "pthread_mutex_lock");

        avail++; // Увеличение количества доступных ресурсов

        s = pthread_mutex_unlock(&mtx); // Освобождение мьютекса
        if (s != 0)
            errExitEN(s, "pthread_mutex_unlock");
    }

    return NULL; // Возврат из потока
}

int
main(int argc, char *argv[])
{
    time_t t = time(NULL); // Начальное время для отсчёта

    int totRequired = 0; // Общее количество ресурсов, которое необходимо произвести

    /* Создание потоков-производителей */
    for (int j = 1; j < argc; j++) {
        totRequired += atoi(argv[j]); // Суммируем количество ресурсов от всех производителей

        pthread_t tid;
        int s = pthread_create(&tid, NULL, producer, argv[j]); // Создаём поток
        if (s != 0)
            errExitEN(s, "pthread_create");
    }

    /* Цикл потребления ресурсов */
    int numConsumed = 0; // Общее количество потребленных ресурсов
    bool done = false; // Флаг завершения работы

    for (;;) {
        int s = pthread_mutex_lock(&mtx); // Захват мьютекса
        if (s != 0)
            errExitEN(s, "pthread_mutex_lock");

        /* Проверяем и обрабатываем доступные ресурсы */
        while (avail > 0) {
            numConsumed++; // Увеличиваем счётчик потреблённых ресурсов
            avail--; // Уменьшаем количество доступных ресурсов

            printf("T=%ld: numConsumed=%d\n", 
                   (long) (time(NULL) - t), numConsumed); // Выводим информацию о времени и количестве потреблённых ресурсов

            /* Проверяем, обработаны ли все ресурсы */
            done = numConsumed >= totRequired;
        }

        s = pthread_mutex_unlock(&mtx); // Освобождение мьютекса
        if (s != 0)
            errExitEN(s, "pthread_mutex_unlock");

        if (done) // Если все ресурсы обработаны, выходим из цикла
            break;

        /* Здесь можно выполнить другие задачи, не требующие блокировки мьютекса */
    }

    exit(EXIT_SUCCESS);
}

/*
Резюме:
Этот код реализует модель "производитель-потребитель" без использования условной переменной.
Производители создают ресурсы (увеличивают переменную `avail`), а потребитель опрашивает 
значение этой переменной и потребляет ресурсы по мере их появления. 

Основные особенности:
- Потоки-производители увеличивают `avail`, блокируя доступ к переменной через мьютекс.
- Потребитель в цикле проверяет доступность ресурсов, опрашивая `avail`.
- Использование подхода "опроса" (polling) вместо уведомления через условные переменные
  делает код менее эффективным для сложных сценариев.
*/