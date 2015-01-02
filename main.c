#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "scan.h"

#define _NANO_MULTIPLIER 1000000000
#define _BEGET_U_MAXCHARS 6

static unsigned int options = 0;
static const unsigned int opt_passive = 1;
static const unsigned int opt_scanlog = 2;
static const unsigned int opt_monothr = 4;

static char *mess_usage =
"Использование: \n\
litedet [ИМЯ ПОЛЬЗОВАТЕЛЯ]... [КЛЮЧ]...\n\
Например: \n\
litedet [beelin7h] -p\n";

static char *mess_arg_wrong =
"Аргументы представлены в неверном формате!\n\
Все аргументы регистрозависимы!\n";

static char *mess_arg_toomany =
"Слишком много аргументов!\n";

char* get_real_path(char *user)
{
    char *root = (char*) malloc(sizeof(char[_POSIX_PATH_MAX]));
    char *home_dir = (char*) malloc(sizeof(char[10+_BEGET_U_MAXCHARS]));
    char *append = (char*) malloc(sizeof(char[10]));
    append = "test";
    strcat(home_dir, "/home/");
    strcat(home_dir, user);
    strcat(home_dir, "/");

    strcat(root, home_dir);
    strcat(root, append);

    return root;
}

int main(int argc, char *argv[])
{
    // ======================= Обработка аргументов
    if(argc == 0)
    {
        printf(mess_usage);
    }
    if(argc > 2)
    {
        printf(mess_arg_toomany);
    }
    char ch;
    ch = argv[2][1];
    if(ch != '-')
    {
        printf(mess_arg_wrong);
        printf(mess_usage);
        return -1;
    }
    ch = argv[2][2];
    switch(ch)
    {
        case 'p':
            options |= opt_passive;
    }
    // ======================= Обработка аргументов

    // ======================= Переменные
    char *user = argv[1];
    struct timespec start, stop;
    // ======================= Переменные

    // ======================= Таймер
    int clock_status = clock_gettime(CLOCK_REALTIME, &start);
    if (clock_status < 0)
    {
        perror("Timer error");
        return 1;
    }
    // ======================= Таймер

    strcpy(user, "kordax");
    char *root = get_real_path(user);
    puts(root);

    // ======================= Рекурсивный поиск в директориях

    fslist *files_list = fs_make();

    walk(files_list, root);
    scan(files_list);

    // ======================= Рекурсивный поиск в директориях
    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * _NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / _NANO_MULTIPLIER;
    printf( "Processing time is %.3Lf seconds!\n", tt);
    return 0;
}
