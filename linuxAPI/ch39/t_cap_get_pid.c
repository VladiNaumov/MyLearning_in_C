/* t_cap_get_pid.c

   Эта программа получает и отображает способности процесса с указанным PID.

   Программа использует системный вызов cap_get_pid для получения текущих возможностей процесса, а затем отображает их в текстовом виде с помощью cap_to_text.

*/

#include <sys/capability.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int main(int argc, char *argv[])
{
    // Проверка аргументов командной строки
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);  // Если PID не указан, вывести инструкцию
        exit(EXIT_FAILURE);
    }

    // Получаем возможности процесса с указанным PID
    cap_t caps = cap_get_pid(atoi(argv[1]));  // Преобразуем PID в целое число
    if (caps == NULL)
        errExit("cap_get_pid");  // В случае ошибки вызовем errExit

    // Преобразуем возможности процесса в текстовый формат
    char *str = cap_to_text(caps, NULL);
    if (str == NULL)
        errExit("cap_to_text");  // В случае ошибки вызовем errExit

    // Выводим возможности процесса
    printf("Capabilities: %s\n", str);

    // Освобождаем память
    cap_free(caps);
    cap_free(str);

    exit(EXIT_SUCCESS);  // Завершаем программу
}

/*
### Объяснение кода:
1. **Проверка аргументов**:
   - Программа ожидает, что пользователь передаст PID процесса через аргументы командной строки. Если PID не передан, программа выводит сообщение о правильном использовании.

2. **cap_get_pid**:
   - Функция `cap_get_pid(pid)` используется для получения текущих возможностей процесса, заданного PID. Она возвращает структуру типа `cap_t`, которая хранит информацию о возможностях процесса.

3. **cap_to_text**:
   - После того как получены возможности процесса, они преобразуются в текстовый формат с помощью функции `cap_to_text`. Это позволяет удобно вывести их для пользователя.

4. **Печать результатов**:
   - После преобразования в текстовый вид, возможности процесса выводятся в терминал.

5. **Очистка памяти**:
   - После использования структуры `cap_t` и строки, полученной с помощью `cap_to_text`, память освобождается функцией `cap_free`.

6. **Пример использования**:
   ```bash
   ./t_cap_get_pid 1234  # Где 1234 - это PID процесса, чьи возможности нужно вывести
   ```

7. **Обработка ошибок**:
   - В случае ошибки при получении возможностей процесса или их преобразовании в текст, программа завершится с выводом соответствующего сообщения об ошибке.
   
*/