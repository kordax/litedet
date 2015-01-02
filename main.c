#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "const.h"
#include "scan.h"

void handle_arg(char *argstr)
{
    switch(arg_is_long)
    {
        case true:
            if(strcmp(argstr, arg_longarg_list[passive]) == 0)      {   opt_bites |= opt_passive;   break;  } // Установка бита пассивного режима
            if(strcmp(argstr, arg_longarg_list[log]) == 0)          {   opt_bites |= opt_log;       break;  } // Установка бита логирования
            if(strcmp(argstr, arg_longarg_list[extlog]) == 0)       {   opt_bites |= opt_extlog;    break;  } // Установка бита расш. логирования
        default:
            if(strcmp(argstr, arg_shortarg_list[passive]) == 0)      {   opt_bites |= opt_passive;   break;  } // Установка бита пассивного режима
            if(strcmp(argstr, arg_shortarg_list[log]) == 0)          {   opt_bites |= opt_log;       break;  } // Установка бита логирования
            if(strcmp(argstr, arg_shortarg_list[extlog]) == 0)       {   opt_bites |= opt_extlog;    break;  } // Установка бита расш. логирования
    }
}

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
    if(argc == 1)
    {
        printf(mess_usage);
        return -1;
    }
    if(argc > 3)
    {
        printf(mess_arg_toomany);
        return -1;
    }

    int n = 1;
    for (int i = 0; i < _MAX_ARGUMENTS && n <= 2; i++)
    {
        sec_arg = strstr(argv[n], arg_longarg_list[i]);
        sec_arg = strstr(argv[n], arg_shortarg_list[i]);
        if(sec_arg != NULL)
        {
            if(strcmp(sec_arg, arg_shortarg_list[i]) == 0)
            {
                arg_is_valid = true;
                sec_arg = arg_shortarg_list[i];
                break;
            }
            if(strcmp(sec_arg, arg_longarg_list[i]) == 0)
            {
                arg_is_long = true;
                arg_is_valid = true;
                sec_arg = arg_longarg_list[i];
                break;
            }
        }
        n++;
    }
    if (sec_arg == NULL)
    {
        if(argc == 2)
        {
            printf(mess_arg_wrong, argv[1]);
            return -1;
        }
        if(argc == 3)
        printf(mess_arg_wrong, argv[2]);
        printf(mess_usage);
        return -1;
    }
    if(arg_is_valid) // Обработаем правильно введённые аргументы
    {
        handle_arg(sec_arg);
    }
    else
    if(argc > 1)
        {
          if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
          {
             printf(mess_usage);
             printf(mess_arg_list);
             return 0;
            }
            if(argc == 2)
            {
                if(argv[1][0] == '-' && arg_is_long)
                {
                    printf(mess_arg_maybe, sec_arg);
                    printf(mess_usage);
                    return -1;
                }
            }
            if(argc == 3)
            if(argv[2][0] != '-')
            {
                printf(mess_arg_maybe, sec_arg);
                printf(mess_usage);
                return -1;
            }
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
