/* 6. Processes */

#include <unistd.h>
#include <stdio.h>

* ============ Управление процессами ============ */
/*
 * getpid - возвращает идентификатор текущего процесса (PID).
 * Возвращает PID текущего процесса.
 */
pid_t getpid(void);

/*
 * getppid - возвращает идентификатор родительского процесса (PPID).
 * Возвращает PPID текущего процесса.
 */
pid_t getppid(void);

/* ============ Работа с окружением ============ */

/*
 * getenv - возвращает значение переменной окружения.
 * name - имя переменной окружения.
 * Возвращает указатель на значение переменной или NULL, если переменная не найдена.
 */
char *getenv(const char *name);

/*
 * putenv - добавляет/изменяет переменную окружения.
 * string - строка формата "VAR=value".
 * Возвращает 0 при успешном выполнении или -1 при ошибке.
 */
int putenv(char *string);

/*
 * setenv - устанавливает значение переменной окружения.
 * name - имя переменной.
 * value - новое значение переменной.
 * overwrite - если 0, не изменяет существующую переменную.
 * Возвращает 0 при успешном выполнении или -1 при ошибке.
 */
int setenv(const char *name, const char *value, int overwrite);

/*
 * unsetenv - удаляет переменную окружения.
 * name - имя переменной.
 * Возвращает 0 при успешном выполнении или -1 при ошибке.
 */
int unsetenv(const char *name);

/*
 * clearenv - очищает все переменные окружения.
 * Возвращает 0 при успешном выполнении.
 */
int clearenv(void);

/* ============ Управление потоком выполнения ============ */

/*
 * setjmp - сохраняет текущее состояние выполнения.
 * env - буфер для сохранения состояния.
 * Возвращает 0 при первом вызове и значение val при вызове longjmp.
 */
int setjmp(jmp_buf env);

/*
 * longjmp - восстанавливает сохранённое состояние выполнения.
 * env - буфер сохранённого состояния.
 * val - значение для возвращения в setjmp (не может быть 0).
 */
void longjmp(jmp_buf env, int val);


int main() {
    pid_t pid = getpid();    // Получаем идентификатор текущего процесса
    pid_t ppid = getppid();  // Получаем идентификатор родительского процесса

    printf("Current process ID (PID): %d\n", pid);
    printf("Parent process ID (PPID): %d\n", ppid);
    return 0;
}

/*
 * Пример использования getenv() и putenv():
 * Эти функции управляют окружением процесса, позволяют добавлять, изменять и
 * извлекать переменные окружения, что полезно для настройки конфигурации приложений.
 */

#include <stdlib.h>
#include <stdio.h>

int main() {
    char *path = getenv("PATH"); // Извлекаем значение переменной окружения PATH
    if (path) {
        printf("PATH: %s\n", path);
    }

    // Устанавливаем новую переменную окружения MY_VAR=123
    if (putenv("MY_VAR=123") != 0) {
        perror("putenv failed");
    } else {
        printf("MY_VAR: %s\n", getenv("MY_VAR"));
    }

    return 0;
}

/*
 * Пример использования setenv() и unsetenv():
 * setenv() позволяет добавлять или изменять переменные окружения, с опцией
 * перезаписи, а unsetenv() удаляет переменные.
 */

#include <stdlib.h>
#include <stdio.h>

int main() {
    if (setenv("NEW_VAR", "Hello", 1) != 0) {  // Добавляем переменную окружения
        perror("setenv failed");
        return 1;
    }
    printf("NEW_VAR: %s\n", getenv("NEW_VAR"));

    // Удаляем переменную окружения
    if (unsetenv("NEW_VAR") != 0) {
        perror("unsetenv failed");
        return 1;
    }
    printf("NEW_VAR after unset: %s\n", getenv("NEW_VAR")); // Должен быть NULL

    return 0;
}

/*
 * Пример использования clearenv():
 * clearenv() очищает все переменные окружения текущего процесса.
 * Будьте осторожны, так как это может нарушить работу других программ,
 * если они зависят от окружения.
 */

#define _BSD_SOURCE  // Устанавливаем для совместимости
#include <stdlib.h>
#include <stdio.h>

int main() {
    if (clearenv() != 0) {
        perror("clearenv failed");
        return 1;
    }

    printf("PATH after clearenv: %s\n", getenv("PATH")); // Должен быть NULL
    return 0;
}

/*
 * Пример использования setjmp() и longjmp():
 * Эти функции создают возможность возврата к сохранённому состоянию, полезны для
 * обработки ошибок, восстановления после сбоев или возврата в безопасное место при ошибке.
 */

#include <setjmp.h>
#include <stdio.h>

jmp_buf env;  // Объявляем буфер для сохранения состояния

void second() {
    printf("Inside second()\n");
    longjmp(env, 1); // Возвращаемся в точку setjmp с ненулевым значением
}

void first() {
    printf("Inside first()\n");
    second();
    printf("This line is never executed.\n");
}

int main() {
    if (setjmp(env) == 0) {  // Сохраняем состояние
        printf("Initial call\n");
        first();
    } else {
        printf("Returned from longjmp\n");
    }
    return 0;
}
