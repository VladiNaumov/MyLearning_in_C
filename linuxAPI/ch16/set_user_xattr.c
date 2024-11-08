/*
пример программы на языке C, которая использует системный вызов `setxattr()` 
для создания или изменения расширенных атрибутов (EA) типа `user`. 
Программа принимает имя файла, имя атрибута и его значение в качестве аргументов командной строки:
*/

/* set_user_xattr.c

   Программа для создания или изменения расширенных атрибутов (EA) типа user с использованием
   системного вызова setxattr().

   Имя файла, имя атрибута и его значение передаются как аргументы командной строки.
*/

#include <sys/xattr.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        usageErr("%s <file> <attr_name> <attr_value>\n", argv[0]);
    }

    const char *file = argv[1];          // Имя файла
    const char *attr_name = argv[2];     // Имя расширенного атрибута
    const char *attr_value = argv[3];    // Значение расширенного атрибута

    // Установка расширенного атрибута
    if (setxattr(file, attr_name, attr_value, strlen(attr_value), 0) == -1) {
        errExit("setxattr");
    }

    printf("Successfully set extended attribute '%s' on file '%s'\n", attr_name, file);

    exit(EXIT_SUCCESS);
}
/*
### Пояснение программы:
1. **Аргументы командной строки**:
   - Программа принимает три аргумента командной строки: имя файла, имя расширенного атрибута и его значение.
   
2. **Системный вызов `setxattr`**:
   - `setxattr()` используется для установки расширенных атрибутов. Она принимает следующие параметры:
     - Имя файла.
     - Имя атрибута (в данном случае это атрибут типа `user`).
     - Значение атрибута.
     - Размер значения атрибута.
     - Флаги (в данном случае установлены флаги по умолчанию — 0).

3. **Ошибка**:
   - Если `setxattr` возвращает ошибку (например, если файл не существует или атрибут нельзя установить), программа завершится с сообщением об ошибке.

4. **Успешное завершение**:
   - После успешного выполнения `setxattr`, программа выводит сообщение о том, что атрибут был установлен.

### Компиляция и запуск:
Для компиляции программы можно использовать команду:

```bash
gcc set_user_xattr.c -o set_user_xattr
```

Чтобы запустить программу, передайте имя файла, имя атрибута и его значение:

```bash
./set_user_xattr myfile user.myattr "This is my value"
```

### Примечания:
- Атрибуты типа `user` могут быть полезны для хранения дополнительных метаданных или других специфичных для пользователя данных в файловой системе.
- Для работы с расширенными атрибутами необходимо, чтобы файловая система поддерживала эту возможность (например, ext4, XFS).

*/