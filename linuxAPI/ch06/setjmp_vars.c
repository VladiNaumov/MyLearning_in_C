/*
 * Этот код демонстрирует, как setjmp и longjmp могут влиять на переменные, в зависимости от их типов и хранения.
 * В частности, он показывает, что переменные с разными спецификаторами (register, volatile) могут вести себя по-разному при возвращении в точку, сохраненную setjmp.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env; /* Переменная для хранения состояния при setjmp */

static void doJump(int nvar, int rvar, int vvar)
{
    printf("Inside doJump(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1); /* Возвращает управление в setjmp с кодом 1 */
}

int main(int argc, char *argv[])
{
    int nvar;              /* Обычная переменная */
    register int rvar;     /* Регистрируемая переменная (по возможности в регистре) */
    volatile int vvar;     /* Переменная с ключевым словом volatile */

    nvar = 111;
    rvar = 222;
    vvar = 333;

    if (setjmp(env) == 0) { /* Код выполняется при первом вызове setjmp, возвращает 0 */
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJump(nvar, rvar, vvar);

    } else { /* Код выполняется после возврата через longjmp */
        printf("After longjmp(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    }

    exit(EXIT_SUCCESS);
}

/*

Инициализация переменных:
nvar, rvar, vvar — три переменные с разными спецификаторами.
nvar — обычная переменная.
rvar — переменная с register, которая предполагает размещение в регистре.
vvar — переменная с volatile, что указывает компилятору избегать оптимизации при работе с этой переменной.

Точка сохранения состояния:
setjmp(env) устанавливает точку сохранения состояния программы.
При первом вызове setjmp возвращает 0, и в этом случае программа изменяет значения nvar, rvar и vvar, а затем вызывает doJump.

Вызов doJump:
Функция doJump выводит текущие значения переменных и вызывает longjmp(env, 1), возвращая управление в setjmp с кодом 1.

Поведение после longjmp:
После возврата к setjmp, выполняется ветка else, где выводятся значения nvar, rvar и vvar.

Специфика типов переменных:
nvar: Обычно сохраняет значение, установленное перед longjmp.
rvar: Поведение может быть непредсказуемым, поскольку регистровые переменные часто не сохраняют значение при longjmp.
vvar: Должна сохранять свое значение даже при longjmp, поскольку volatile заставляет компилятор сохранять изменения.
 * */