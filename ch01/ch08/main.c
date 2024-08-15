#include <stdio.h>

// Определение структуры Rectangle
typedef struct {
    float width;      // Ширина
    float height;     // Высота
    float area;       // Площадь
    float perimeter;  // Периметр
} Rectangle;

// Функция для создания прямоугольника и вычисления его свойств
Rectangle create_rectangle(Rectangle rect, float width, float height) {
    rect.width = width;            // Устанавливаем ширину
    rect.height = height;          // Устанавливаем высоту
    rect.area = width * height;    // Вычисляем площадь
    rect.perimeter = 2 * (width + height); // Вычисляем периметр
    return rect;                   // Возвращаем заполненную структуру
}

/*

Передача структуры по значению
Когда ты передаёшь структуру по значению в функцию, ты создаёшь копию этой структуры.
В функции ты работаешь с копией, а не с оригиналом.
Это значит, что любые изменения, сделанные с этой копией, не будут влиять на оригинальную структуру вне функции.

При передаче структуры по значению создаётся копия всей структуры, что может быть неэффективно, если структура большая.
*/

// Функция для вывода свойств прямоугольника
void print_rectangle(Rectangle rect) {
    printf("Rectangle:\n");
    printf("Width: %.2f\n", rect.width);
    printf("Height: %.2f\n", rect.height);
    printf("Area: %.2f\n", rect.area);
    printf("Perimeter: %.2f\n", rect.perimeter);
}

int main() {

     Rectangle rec;
    // Создание прямоугольника через функцию create_rectangle
    Rectangle myRect = create_rectangle(rec, 5.0, 3.0);

    // Вывод свойств прямоугольника на экран
    print_rectangle(myRect);

    return 0;
}

/*   способ второй   */

// Определение структуры Rectangle
typedef struct {
    float width;      // Ширина
    float height;     // Высота
    float area;       // Площадь
    float perimeter;  // Периметр
} Rectangle;

// Функция для создания прямоугольника и вычисления его свойств
Rectangle create_rectangle(Rectangle *rect, float width, float height) {
    rect->width = width;            // Устанавливаем ширину
    rect->height = height;          // Устанавливаем высоту
    rect->area = width * height;    // Вычисляем площадь
    rect->perimeter = 2 * (width + height); // Вычисляем периметр
    return *rect;                   // Возвращаем заполненную структуру
}

/*
    Передача указателя на структуру
    Когда ты передаёшь указатель на структуру, ты передаёшь адрес оригинальной структуры.
    Это позволяет функции напрямую изменять структуру, поскольку она работает с оригинальными данными, а не с их копией.
*/

// Функция для вывода свойств прямоугольника
void print_rectangle(Rectangle rect) {
    printf("Rectangle:\n");
    printf("Width: %.2f\n", rect.width);
    printf("Height: %.2f\n", rect.height);
    printf("Area: %.2f\n", rect.area);
    printf("Perimeter: %.2f\n", rect.perimeter);
}

int main() {

    Rectangle *rec;
    // Создание прямоугольника через функцию create_rectangle
    Rectangle myRect = create_rectangle(rec, 5.0, 3.0);

    // Вывод свойств прямоугольника на экран
    print_rectangle(myRect);

    return 0;
}

/*
Основные различия

Копирование данных: При передаче структуры по значению создаётся копия всей структуры,
что может быть неэффективно, если структура большая. При передаче указателя копии не создаются,
передается только адрес, что экономит память и время.

Изменение оригинала: При передаче по значению функция работает с копией и не изменяет оригинальные данные.
При передаче указателя функция работает с оригиналом и может его изменить.

Безопасность: Передача по значению безопаснее, так как функция не может случайно изменить данные вне своей области видимости.
Передача указателя позволяет изменять данные, но требует более осторожного подхода.


При динамическом выделении памяти ты работаешь с указателями, поскольку именно указатель возвращается функцией выделения памяти.
Другого способа передачи данных в функции, кроме как через указатель, нет, поскольку сама структура как объект в таком случае существует только в памяти, доступной через указатель.


*/