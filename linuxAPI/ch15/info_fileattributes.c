/* 15 File Attributes */

/*
Системный вызов stat() извлекает информацию о файле (метаданные), основная часть 
которой берется из индексного дескриптора файла. К ней относятся сведения о принад-
лежности файла, о правах доступа к нему, а также метки времени.
Программа может обновить время последнего доступа к файлу и время его послед-
него изменения, выполнив системные вызовы utime(), utimes() или другие подобные 
интерфейсы.
Каждый файл имеет относящиеся к нему идентификаторы пользователя (владельца) 
и группы, а также набор битов прав доступа. Для организации прав доступа пользователи 
файла распределены по трем категориям: владелец (известный также как пользователь), 
группа и остальные. Каждой категории могут быть предоставлены следующие права до-
ступа: чтение, запись и выполнение. Эта же схема используется для каталогов, хотя для них 
биты прав доступа имеют немного другое значение. Системные вызовы chown() и chmod() 
меняют принадлежность и права доступа к файлу. Системный вызов umask() задает маску 
битов прав доступа, которые всегда отключаются, когда вызывающий процесс создает 
файл.
Для файлов и каталогов задействуют три дополнительных бита прав доступа. Биты 
set-user-ID и set-group-ID можно применить к программным файлам, чтобы создать 
программы, которые вызывают появление у выполняющегося процесса  привилегий, 
отличающихся от привилегий программного файла за счет присвоения другого иден-
тификатора пользователя или группы. Для каталогов, расположенных в файловых 
системах, смонтированных с параметром nogrpid (sysvgroups), бит set-group-ID мож-
но использовать для контроля над тем, откуда будут наследовать GID новые файлы, 
создаваемые в данном каталоге: от действующего GID для процесса или же от GID для 
родительского каталога. Применительно к каталогам бит закрепления действует как 
флаг, запрещающий удаление.
Флаги индексного дескриптора управляют различными вариантами поведения фай-
лов и каталогов. Несмотря на то что изначально они были определены для файловой 
системы ext2, теперь эти флаги поддерживаются и в некоторых других системах.

 */
 

#include <sys/stat.h>

/*
 * stat - Получает информацию о файле по его пути и записывает её в структуру stat.
 * Параметры:
 *   pathname - путь к файлу;
 *   statbuf - указатель на структуру stat, куда будет записана информация.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int stat(const char *pathname, struct stat *statbuf);

/*
 * lstat - Аналогична stat, но если pathname указывает на символическую ссылку, 
 *         lstat возвращает информацию о самой ссылке, а не о файле, на который она указывает.
 * Параметры:
 *   pathname - путь к файлу или символической ссылке;
 *   statbuf - указатель на структуру stat, куда будет записана информация.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int lstat(const char *pathname, struct stat *statbuf);

/*
 * fstat - Получает информацию о файле, используя файловый дескриптор.
 * Параметры:
 *   fd - файловый дескриптор;
 *   statbuf - указатель на структуру stat, куда будет записана информация.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int fstat(int fd, struct stat *statbuf);

#include <utime.h>

/*
 * utime - Изменяет время последнего доступа и модификации файла.
 * Параметры:
 *   pathname - путь к файлу;
 *   buf - указатель на структуру utimbuf с новыми временами. Если NULL, 
 *         устанавливает текущее время.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int utime(const char *pathname, const struct utimbuf *buf);

#include <sys/time.h>

/*
 * utimes - Устанавливает время последнего доступа и модификации файла с большей точностью.
 * Параметры:
 *   pathname - путь к файлу;
 *   tv - массив из двух элементов timeval, указывающий времена.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int utimes(const char *pathname, const struct timeval tv[2]);

/*
 * futimes - Аналогична utimes, но работает с файловым дескриптором.
 * Параметры:
 *   fd - файловый дескриптор;
 *   tv - массив timeval, указывающий времена.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int futimes(int fd, const struct timeval tv[2]);

/*
 * lutimes - Аналогична utimes, но изменяет время символической ссылки, а не файла, 
 *           на который она указывает.
 * Параметры:
 *   pathname - путь к символической ссылке;
 *   tv - массив timeval, указывающий времена.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int lutimes(const char *pathname, const struct timeval tv[2]);

#define _XOPEN_SOURCE 700     /* Для использования POSIX API */
#include <sys/stat.h>

/*
 * utimensat - Устанавливает время последнего доступа и модификации файла с высокой точностью.
 *             Поддерживает флаги и относительные пути.
 * Параметры:
 *   dirfd - файловый дескриптор каталога;
 *   pathname - путь к файлу;
 *   times - массив timespec для указания времён;
 *   flags - флаги (например, AT_SYMLINK_NOFOLLOW).
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags);

#include _GNU_SOURCE
#include <sys/stat.h>

/*
 * futimens - Устанавливает время доступа и модификации для файла по его дескриптору с использованием timespec.
 * Параметры:
 *   fd - файловый дескриптор;
 *   times - массив timespec, содержащий времена.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int futimens(int fd, const struct timespec times[2]);

#include <unistd.h>

/*
 * chown - Изменяет владельца и группу файла.
 * Параметры:
 *   pathname - путь к файлу;
 *   owner - новый идентификатор владельца;
 *   group - новый идентификатор группы.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int chown(const char *pathname, uid_t owner, gid_t group);

#define _XOPEN_SOURCE 500     /* Для использования расширенного POSIX API */
#include <unistd.h>

/*
 * lchown - Аналогична chown, но изменяет владельца символической ссылки, 
 *          не затрагивая файл, на который она указывает.
 * Параметры:
 *   pathname - путь к символической ссылке;
 *   owner - новый идентификатор владельца;
 *   group - новый идентификатор группы.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int lchown(const char *pathname, uid_t owner, gid_t group);

/*
 * fchown - Изменяет владельца и группу файла по файловому дескриптору.
 * Параметры:
 *   fd - файловый дескриптор;
 *   owner - новый идентификатор владельца;
 *   group - новый идентификатор группы.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int fchown(int fd, uid_t owner, gid_t group);

#include <unistd.h>

/*
 * access - Проверяет права доступа к файлу.
 * Параметры:
 *   pathname - путь к файлу;
 *   mode - режим проверки (например, R_OK для чтения).
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int access(const char *pathname, int mode);

#include <sys/stat.h>

/*
 * umask - Устанавливает маску создания файлов, которая управляет правами по умолчанию.
 * Параметры:
 *   mask - новая маска.
 * Возвращает: предыдущую маску.
 */
mode_t umask(mode_t mask);

#include <sys/stat.h>

/*
 * chmod - Изменяет права доступа к файлу.
 * Параметры:
 *   pathname - путь к файлу;
 *   mode - новый режим прав доступа.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int chmod(const char *pathname, mode_t mode);

#define _XOPEN_SOURCE 500     /* Для использования расширенного POSIX API */
#include <sys/stat.h>

/*
 * fchmod - Изменяет права доступа к файлу, используя файловый дескриптор.
 * Параметры:
 *   fd - файловый дескриптор;
 *   mode - новый режим прав доступа.
 * Возвращает: 0 при успехе, -1 при ошибке.
 */
int fchmod(int fd, mode_t mode);