/* Для проверки утверждения, что вызов `getppid()` в дочерних процессах возвращает 1 (идентификатор процесса `init`), 
можно создать программу, которая создает несколько дочерних процессов, и в каждом из них вызывает `getppid()` 
для проверки родительского процесса. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Создаем дочерний процесс

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) { // В дочернем процессе
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else { // В родительском процессе
        // Ожидаем, чтобы убедиться, что дочерний процесс уже завершен и получил init в качестве родителя
        sleep(2); // Даем время для завершения дочернего процесса
        printf("Parent process: PID = %d\n", getpid());
    }

    return 0;
}
/*

### Объяснение:
- Родительский процесс создает дочерний процесс с помощью `fork()`.
- В дочернем процессе вызывается `getppid()`, который должен вернуть 1, так как процесс init (PID 1) будет родителем для всех процессов, завершившихся после выхода родительского процесса.
- В родительском процессе мы используем `sleep(2)`, чтобы дать время дочернему процессу завершиться и быть пересозданным с родителем `init`.

Для проверки утверждения:
1. Запустите программу.
2. После завершения родительского процесса дочерний процесс должен стать процессом с родителем `init`, и вызов `getppid()` в дочернем процессе должен вернуть 1.

Этот код работает в Unix-подобных системах, где процесс `init` имеет PID 1.
*/