/* 33 Threads: Further Details */

#include <signal.h>

/*
 * pthread_sigmask - Изменяет или проверяет маску сигналов вызывающего потока.
 * how - Определяет поведение (SIG_BLOCK, SIG_UNBLOCK или SIG_SETMASK).
 * set - Указатель на новую маску сигналов (или NULL для отсутствия изменений).
 * oldset - Указатель для сохранения предыдущей маски сигналов (или NULL, если не требуется).
 * Возвращает 0 при успехе или ненулевой код ошибки.
 */
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

/*
 * pthread_kill - Отправляет сигнал определённому потоку.
 * thread - Идентификатор потока, которому будет отправлен сигнал.
 * sig - Номер отправляемого сигнала.
 * Возвращает 0 при успехе или ненулевой код ошибки.
 */
int pthread_kill(pthread_t thread, int sig);

/*
 * pthread_sigqueue (расширение GNU) - Отправляет сигнал с сопутствующим значением определённому потоку.
 * thread - Идентификатор потока, которому будет отправлен сигнал.
 * sig - Номер отправляемого сигнала.
 * value - Union, содержащий сопутствующее значение.
 * Возвращает 0 при успехе или ненулевой код ошибки.
 */
#define _GNU_SOURCE
int pthread_sigqueue(pthread_t thread, int sig, const union sigval value);

/*
 * sigwait - Приостанавливает выполнение до получения одного из сигналов из набора.
 * set - Набор сигналов, указывающий, какие сигналы ожидать.
 * sig - Указатель для сохранения номера сигнала, вызвавшего возврат.
 * Возвращает 0 при успехе или ненулевой код ошибки.
 */
int sigwait(const sigset_t *set, int *sig);





