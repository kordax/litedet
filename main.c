#include <stdio.h>
#include <string.h>
#include <dirent.h> // opendir, closedir, readdir, rewinddir и Co.
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dirlist.h"
#include <time.h>

#define NANO_MULTIPLIER 1000000000

int main(int argc, char *argv[])
{
    struct stat filestat_info;
    struct timespec start, stop;
    int clock_status = clock_gettime(CLOCK_REALTIME, &start);
    if (clock_status < 0)
    {
        perror("Timer error");
        return 1;
    }

    char dir_prefix[] = "/media/kordax/7c1bb3dc-12a8-46d6-b140-58c8a60fff94/";
    char dir_append[32];
    char dir_name[sizeof(dir_prefix) + 34] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(dir_name, dir_prefix);
    strcat(dir_name, dir_append);

    puts(dir_name);

    dir_list* dl = get_dir_content(dir_name);

    if(lstat(dir_name, &filestat_info) < 0)
    {
        perror(dir_name);
        return 1;
    }

    if (!S_ISDIR(filestat_info.st_mode))
    {
        puts("It is not a dir!");
    }

    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / NANO_MULTIPLIER;
    printf( "Processing time is %.3Lf seconds!\n", tt);
    return 0;
}

