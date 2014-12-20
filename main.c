#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "walk.h"

#define NANO_MULTIPLIER 1000000000
#define MAX_SUBDIR_CHARS 50

int main(int argc, char *argv[])
{
    //pid_t fokr_pid = fork();
    struct timespec start, stop;
    int clock_status = clock_gettime(CLOCK_REALTIME, &start);
    if (clock_status < 0)
    {
        perror("Timer error");
        return 1;
    }

    char dir_prefix[] = "/home/kordax/";
    char dir_append[_POSIX_PATH_MAX];
    char base_dir[_POSIX_PATH_MAX] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(base_dir, dir_prefix);
    strcat(base_dir, dir_append);

    puts(base_dir);

    // ======================= Рекурсивный поиск в директориях

    fslist *files_list = fs_make();
    char root[_POSIX_PATH_MAX] = {0};
    strcpy(root, base_dir);

    walk(files_list, root);

    // ======================= Рекурсивный поиск в директориях
    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / NANO_MULTIPLIER;
    printf( "Processing time is %.3Lf seconds!\n", tt);
    return 0;
}
