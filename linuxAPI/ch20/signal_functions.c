/*
Этот файл содержит полезные функции для работы с сигналами в Unix-подобных системах. В частности, функции для печати информации о наборе сигналов, маске блокированных сигналов и ожидающих сигналов для процесса.

### Функции:

1. **`printSigset`**:  
   Печатает список сигналов в наборе сигналов.

*/

   void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
   {
       int sig, cnt;
       cnt = 0;

       for (sig = 1; sig < NSIG; sig++) {
           if (sigismember(sigset, sig)) {
               cnt++;
               fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
           }
       }

       if (cnt == 0)
           fprintf(of, "%s<empty signal set>\n", prefix);
   }
/*

   **Описание:**
   - Эта функция принимает набор сигналов (`sigset_t *sigset`) и печатает все сигналы, которые входят в этот набор.
   - Для каждого сигнала выводится его номер и соответствующее описание с использованием функции `strsignal`.
   - Если в наборе нет активных сигналов, выводится сообщение `<empty signal set>`.

2. **`printSigMask`**:  
   Печатает текущую маску заблокированных сигналов для процесса.
*/
   int printSigMask(FILE *of, const char *msg)
   {
       sigset_t currMask;

       if (msg != NULL)
           fprintf(of, "%s", msg);

       if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1)
           return -1;

       printSigset(of, "\t\t", &currMask);

       return 0;
   }
/*

   **Описание:**
   - Функция выводит маску заблокированных сигналов для текущего процесса, используя `sigprocmask` с флагом `SIG_BLOCK`, чтобы получить текущие заблокированные сигналы.
   - Результат выводится с использованием функции `printSigset`.

3. **`printPendingSigs`**:  
   Печатает список сигналов, которые ожидают обработки для процесса.
*/
   int printPendingSigs(FILE *of, const char *msg)
   {
       sigset_t pendingSigs;

       if (msg != NULL)
           fprintf(of, "%s", msg);

       if (sigpending(&pendingSigs) == -1)
           return -1;

       printSigset(of, "\t\t", &pendingSigs);

       return 0;
   }

/*

   **Описание:**
   - Функция выводит все сигналы, которые ожидают обработки, с использованием `sigpending`.
   - Результат выводится через функцию `printSigset`.

### Примечания:
- **Асинхронная безопасность:** Все функции, использующие `fprintf()`, не являются асинхронно безопасными, поэтому они не должны вызываться из обработчиков сигналов. Это важно, поскольку вызовы, не являющиеся асинхронно безопасными, могут привести к непредсказуемому поведению при обработке сигналов.

- **Типы данных:**
   - `sigset_t`: Тип данных для набора сигналов.
   - `NSIG`: Константа, определяющая максимальное количество сигналов в системе.

### Пример использования:

Если вы хотите отследить текущие заблокированные сигналы в процессе, вы можете использовать функцию `printSigMask`, которая выведет соответствующую информацию:


printSigMask(stdout, "Blocked signals:\n");


Аналогично, если нужно узнать о сигнале, ожидающем обработки:

printPendingSigs(stdout, "Pending signals:\n");


Это удобные утилиты для отладки и мониторинга сигналов в процессе.
*/