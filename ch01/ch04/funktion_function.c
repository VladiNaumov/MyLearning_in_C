/* В C функции также могут принимать другие функции в качестве аргументов, используя указатели на функции.  */

#include <stdio.h>

// Функция, которая принимает целое число и возвращает его квадрат
int square(int x) {
    return x * x;
}

// Функция, которая принимает другую функцию (указатель на функцию) и целое число
int apply_function(int (*func)(int), int value) {
    return func(value);
}

int main() {
    int number = 5;

    // Передаем функцию square в apply_function
    int result = apply_function(square, number);

    printf("Квадрат %d равен %d\n", number, result);

    return 0;
}

/*
 *
 * Объяснение:
    square: Это обычная функция, которая принимает целое число и возвращает его квадрат.
    apply_function: Эта функция принимает два аргумента:
    int (*func)(int): указатель на функцию, которая принимает один int и возвращает int.
    int value: целое число, которое будет передано в функцию func.
    Функция apply_function вызывает func(value) и возвращает результат.
    main: В основной функции программы мы объявляем число number, которое равно 5.
    Затем мы передаем указатель на функцию square и значение number в apply_function. Результат вычисления выводится на экран.
* */