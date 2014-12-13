#include <stdio.h>
#include <string.h>
#include <dirent.h> // opendir, closedir, readdir, rewinddir и Co.
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filelist.h"
#include <time.h>

#define NANO_MULTIPLIER 1000000000
#define MAX_SUBDIR_CHARS 50
#define MAX_DIR_CHARS 128


int main(int argc, char *argv[])
{
    //pid_t fokr_pid = fork();

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
    char home_dir[sizeof(dir_prefix) + sizeof(dir_append)] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(home_dir, dir_prefix);
    strcat(home_dir, dir_append);

    puts(home_dir);

    file_list* dl = get_dir_content(home_dir);

    int cnt = 0;
    while(cnt < dl->size)
    {
        file_node* tmpdir = dl_get(dl, cnt);
        char dir_name[sizeof(sizeof(home_dir)) + MAX_SUBDIR_CHARS] = {0};
        strcat(dir_name, home_dir);
        strcat(dir_name, tmpdir->value->d_name);

        if(lstat(dir_name, &filestat_info) < 0) // tmpdir->value->d_name монструозно))
        {
            perror(dir_name);
            return 1;
        }

        if (!S_ISDIR(filestat_info.st_mode))
        {
            puts("It is not a dir!");
        }

        cnt++;
    }

    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / NANO_MULTIPLIER;
    printf( "Processing time is %.3Lf seconds!\n", tt);
    return 0;
}
