
## Lerning in C

- ch01 Bit operations
- ch02 Pointers
- ch03 Array + pointer
- ch04 Struct + pointer


### Compiling

- gcc app.c
- gcc app.c -o app.exe


- gcc -std=c99 -Wall -pedantic app.c -o app.exe
- gcc -std=c11 -Wall -pedantic app.c -o app.exe
- gcc -std=c17 -Wall -pedantic app.c -o app.exe
- gcc -std=c23 -Wall -pedantic app.c -o app.exe

- gcc -E app.c (компиляции в единицу трансляции)
- gcc -S app.c (компиляция в асcамблер код)
- gcc -c app.c (компиляция в машинный код "объектный файл")

- gcc --version
- gcc --help
- gcc target-help

