/* siginterrupt.c

   Реализация функции библиотеки siginterrupt(3).
   Программа реализует функцию библиотеки `siginterrupt(3)`, которая позволяет изменять поведение системных вызовов в случае получения сигнала.
*/
#include <stdio.h>
#include <signal.h>

int
siginterrupt(int sig, int flag)
{
    int status;
    struct sigaction act;

    // Получение текущей информации о сигнале
    status = sigaction(sig, NULL, &act);
    if (status == -1)
        return -1;  // Возвращаем ошибку, если sigaction не удался

    // Если flag равен 1, убираем флаг SA_RESTART, чтобы системные вызовы не перезапускались
    if (flag)
        act.sa_flags &= ~SA_RESTART;
    else
        act.sa_flags |= SA_RESTART;  // Включаем флаг SA_RESTART

    // Устанавливаем измененные параметры сигнала
    return sigaction(sig, &act, NULL);
}
/*

### Описание работы программы

1. **Функция `siginterrupt`:**  
   Эта функция используется для изменения поведения системных вызовов, которые могут быть автоматически перезапущены после получения сигнала. По умолчанию многие системные вызовы, такие как `read()`, `write()` и `select()`, перезапускаются после получения сигнала. Если флаг `SA_RESTART` установлен, системные вызовы перезапускаются, если сигнал прерывает их выполнение.

2. **Аргументы:**
   - `sig`: Сигнал, для которого нужно изменить флаг поведения.
   - `flag`: Устанавливает, будет ли сигнал перезапускать системные вызовы:
     - Если `flag` равен 1, то флаг `SA_RESTART` убирается, и системные вызовы не будут перезапускаться.
     - Если `flag` равен 0, флаг `SA_RESTART` устанавливается, и системные вызовы будут перезапускаться.

3. **Алгоритм:**
   - Функция использует `sigaction` для получения текущих параметров сигнала.
   - Затем она изменяет флаг `SA_RESTART` в зависимости от значения `flag`.
   - Наконец, она применяет изменения с помощью `sigaction`.

### Примечания

- **SA_RESTART** — это флаг, который используется для указания, что системный вызов, прерванный сигналом, должен быть перезапущен. Если этот флаг сброшен, то системный вызов вернет ошибку с кодом `EINTR` вместо того, чтобы быть автоматически перезапущенным.
- Эта функция полезна для контроля над поведением сигналов в асинхронных системах, где важно управлять тем, как сигналы воздействуют на выполняемые системные вызовы.
*/