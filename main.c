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

    // ======================= Рекурсивный поиск в директориях

    while(dl != NULL)
    {
        while(cnt < dl->size)
        {
            file_node* tmp_file = dl_get(dl, cnt);
            char file_name[sizeof(sizeof(main_file)) + MAX_SUBDIR_CHARS + 30] = {0};
            strcat(file_name, main_file);
            strcat(file_name, "/");
            strcat(file_name, tmp_file->value->d_name);

            puts(file_name);

            if(lstat(file_name, &filestat_info) == -1)
            {
                perror(file_name);
                return 1;
            }
            if (S_ISDIR(filestat_info.st_mode))
            {
                subdir_number++;
                dl = get_dir_content(file_name);
            }
            cnt++;
        }
    }

    // ======================= Рекурсивный поиск в директориях

    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / NANO_MULTIPLIER;
    printf( "Processing time is %.3Lf seconds!\n", tt);
    return 0;
}
