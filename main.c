#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "scan.h"

#define _NANO_MULTIPLIER 1000000000
#define _BEGET_U_MAXCHARS 10

char* get_real_path(char *user)
{
    char *root = (char*) malloc(sizeof(char[_POSIX_PATH_MAX]));
    char *home_dir = (char*) malloc(sizeof(char[10+_BEGET_U_MAXCHARS]));
    char *append = (char*) malloc(sizeof(char[10]));
    append = "test";
    strcat(home_dir, "/home/");
    strcat(home_dir, user);
    strcat(home_dir, "/");
    // ======================= Переменные

    strcat(root, home_dir);
    strcat(root, append);

    return root;
}

int main(int argc, char *argv[])
{

    // ======================= Переменные
    char user[_BEGET_U_MAXCHARS] = {0};
    struct timespec start, stop;
    int clock_status = clock_gettime(CLOCK_REALTIME, &start);
    if (clock_status < 0)
    {
        perror("Timer error");
        return 1;
    }

<<<<<<< HEAD
    char dir_prefix[] = "/home/kordax/";
    char dir_append[32];
    char main_file[sizeof(dir_prefix) + sizeof(dir_append)] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(main_file, dir_prefix);
    strcat(main_file, dir_append);

    puts(main_file);

    file_list* dl = get_dir_content(main_file);

    //if ((fork()) != 0)
    int cnt = 0;
    int subdir_number = 0;
=======
    //scanf("%s", user);
    strcpy(user, "kordax");
    char *root = get_real_path(user);
    puts(root);
>>>>>>> 4a45061c06b7e2a7455a5e31cf39e9757aa96f4b

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
