/* t_execve.c

   Демонстрация использования execve() для выполнения программы.
*/

#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    char *argVec[10];           /* Больше, чем требуется */
    char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    /* Создаем список аргументов для новой программы */

    argVec[0] = strrchr(argv[1], '/');      /* Получаем базовое имя из argv[1] */
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;           /* Список должен заканчиваться NULL */

    /* Выполняем программу, указанную в argv[1] */

    execve(argv[1], argVec, envVec);
    errExit("execve");          /* Если мы здесь, значит, что-то пошло не так */
}

/*
### Резюме кода

Программа демонстрирует использование `execve()` для выполнения другой программы с указанными аргументами и окружением. 
Программа принимает в качестве аргумента путь к исполняемому файлу, который необходимо запустить. 
Она создает список аргументов `argVec`, где первый элемент — это имя запускаемого файла, а второй и третий элементы — строки `"hello world"` и `"goodbye"`. 
Затем вызывается `execve()` для запуска программы, передавая ей список аргументов `argVec` и список переменных окружения `envVec`. 
Если `execve()` завершается ошибкой, программа выводит сообщение об ошибке.

### Ключевые моменты

- `argVec` — это массив аргументов для исполняемой программы, который завершается `NULL`.
- `envVec` — это массив переменных окружения, также заканчивающийся `NULL`.
- `execve()` замещает текущий процесс новой программой, поэтому в случае успеха код после `execve()` не выполняется.
*/