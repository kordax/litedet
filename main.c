#include <stdio.h>
#include <string.h>
#include <dirent.h> // opendir, closedir, readdir, rewinddir и Co.
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "scanner.h"
#include "filemap.h"

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

    char dir_prefix[] = "/media/kordax/7c1bb3dc-12a8-46d6-b140-58c8a60fff94/";
    char dir_append[_POSIX_PATH_MAX];
    char base_dir[_POSIX_PATH_MAX] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(base_dir, dir_prefix);
    strcat(base_dir, dir_append);

    puts(base_dir);

    // ======================= Рекурсивный поиск в директориях

    DIR* cur_dir_ptr;
    struct dirent* entry;
    struct stat filestat;
    char cur_dir[_POSIX_PATH_MAX] = {0};

    strcpy(cur_dir, base_dir);

    cur_dir_ptr = opendir(cur_dir);
    if(cur_dir_ptr == NULL)
    {
        perror(cur_dir_ptr);
        return 1;
    }
    int cnt = 0;
    file_list* readed_files;
    readed_files = make_dirlist();
    char cur_file[_POSIX_PATH_MAX] = {0};
    char tmp_name[_POSIX_PATH_MAX] = {0};
    while (entry) // Пока есть директории
    {
        entry = readdir(cur_dir_ptr);
        puts(entry->d_name);
        strcpy(tmp_name, cur_dir);
        strcat(tmp_name, "/");
        strcat(tmp_name, entry->d_name);
        puts("tmp_name is: ");
        puts(tmp_name);
        if (readed_files->beg != NULL)
        if (strcmp(tmp_name, dl_get_by_name(readed_files, cur_dir)) != 0)
        if ((entry != NULL) && (entry->d_name[0] != '.')) // Если не ./ и не ../
        {
            strcat(cur_dir, "/");
            //strcat(cur_dir, entry->d_name); // Папка или файл на данный момент
            if(entry->d_type == DT_REG)
            {
                strcpy(cur_file, cur_dir);
                strcat(cur_file, entry->d_name);
                scan(cur_file);
                dl_pushback(readed_files, entry);
            }
            if(entry->d_type == DT_DIR)
            {
                strcat(cur_dir, entry->d_name);
                dl_pushback(readed_files, entry);
                cur_dir_ptr = opendir(cur_dir);
                puts(cur_dir);
                cnt++;
            }
        }
        if(!entry) // Если записей больше нет
        {
            int i = 0;
            /*while (i < cnt)
            {
                strcat(cur_dir, "/.."); // Вписываем количество вложений, по которым перешли
                i++;
            }*/

            if (lstat(cur_dir, &filestat) < 0)
            {
                    perror(cur_dir);
                    return 1;
            }
            if(S_ISDIR(filestat.st_mode))
            {
                strcat(cur_dir, "../");
            }
            else
            strcat(cur_dir, "/../");
            char real_path[_POSIX_PATH_MAX] = {0};
            puts("real_ptr dir is: ");
            puts(cur_dir);
            char* real_ptr = realpath(cur_dir, real_path);
            puts(real_path);
            if(real_ptr == NULL)
            {
                perror(real_ptr);
                return 1;
            }
            cur_dir_ptr = opendir(real_path); // Возвращаемся назад на это количество вложений
            puts("opendir real_path is: ");
            puts(real_path);
            if(cur_dir_ptr == NULL)
            {
                perror(cur_dir_ptr);
                return 1;
            }
            strncpy(cur_dir, real_path, sizeof(base_dir)); // Вернулись в базу
            puts("now we are here: ");
            puts(cur_dir);

            cnt = cnt - i;

            cur_dir_ptr = opendir(cur_dir);
            entry = readdir(cur_dir_ptr);
        }
    }
    if (lstat(cur_dir, &filestat) < 0)
    {
            perror(cur_dir);
            return 1;
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
