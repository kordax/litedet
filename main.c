#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include "const.h"
#include "scan.h"

static char *sec_arg;
static fslist *list;
bool arg_is_long                =   false;
bool arg_is_valid               =   false;

static struct timespec start, stop;
static int clock_status;
static unsigned int fork_range;
static unsigned int fork_counter;
static unsigned int fork_remainder;

void handle_arg(char *argstr)
{
    switch(arg_is_long)
    {
        case true:                                                                                            // arg_longarg_list и arg_shortarg_list определены в файле const.h
            if(strcmp(argstr, arg_longarg_list[active]) == 0)       {   opt_bites |= opt_active;    break;  } // Установка бита активного режима
            if(strcmp(argstr, arg_longarg_list[log]) == 0)          {   opt_bites |= opt_log;       break;  } // Установка бита логирования
            if(strcmp(argstr, arg_longarg_list[extlog]) == 0)       {   opt_bites |= opt_extlog;    break;  } // Установка бита расш. логирования
            if(strcmp(argstr, arg_longarg_list[debug]) == 0)        {   opt_bites |= opt_debug;     break;  } // Установка бита режима отладки
            if(strcmp(argstr, arg_longarg_list[mono]) == 0)         {   opt_bites |= opt_monothr;   break;  } // Установка бита режима монопоточности
        default:
            if(strcmp(argstr, arg_shortarg_list[active]) == 0)      {   opt_bites |= opt_active;    break;  } // Установка бита активного режима
            if(strcmp(argstr, arg_shortarg_list[log]) == 0)         {   opt_bites |= opt_log;       break;  } // Установка бита логирования
            if(strcmp(argstr, arg_shortarg_list[extlog]) == 0)      {   opt_bites |= opt_extlog;    break;  } // Установка бита расш. логирования
            if(strcmp(argstr, arg_shortarg_list[debug]) == 0)       {   opt_bites |= opt_debug;     break;  } // Установка бита режима отладки
            if(strcmp(argstr, arg_shortarg_list[mono]) == 0)        {   opt_bites |= opt_monothr;   break;  } // Установка бита режима монопоточности
    }
}

char* get_real_path(char *user)
{
    char *root = (char*) malloc(sizeof(char[_POSIX_PATH_MAX]));
    char *home_dir = (char*) malloc(sizeof(char[10+_LITE_MAX_UNAMESIZE]));
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
    preload();

    pid = getpid();

    if (pid != 0)
    {

        // ======================= Обработка аргументов

        if(argc <= 1)
        {
            printf(mess_usage);
            return -1;
        }
        if(argc > 3)
        {
            printf(mess_arg_toomany);
            return -1;
        }
        if(argc == 3)
        {
            if(argv[2][0] != '-')
            {
                printf(mess_arg_maybe, argv[2]);
                printf(mess_usage);
                return -1;
            }
        }

        for (int i = 0; i < _LITE_OPTIONS; i++)
        {
            if (sec_arg == NULL) sec_arg = strstr(argv[argc - 1], arg_longarg_list[i]);
            if (sec_arg == NULL) sec_arg = strstr(argv[argc - 1], arg_shortarg_list[i]);
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
        }

        if(arg_is_valid) // Обработаем правильно введённые аргументы
        {
            handle_arg(sec_arg);
        }
        if (strcmp(argv[argc - 1], "--help") == 0 || strcmp(argv[argc - 1], "-h") == 0)
        {
            printf(mess_usage);
            printf(mess_arg_list);
            return 0;
        }
        if (argc == 3)
        if (sec_arg == NULL)
        {
            printf(mess_arg_wrong, argv[argc - 1]);
            printf(mess_usage);
            return -1;
        }

        // ======================= Обработка аргументов

    } // pid != 0

    /*
     * Таймер
    */

    if(opt_bites & opt_debug)
    {
        clock_status = clock_gettime(CLOCK_REALTIME, &start);
        if (clock_status < 0)
        {
            perror("Timer error");
            return 1;
        }
    }

    /*
     * Таймер
    */

    // ======================= Рекурсивный поиск в директориях

    char *user = argv[1];
    char *root = get_real_path(user);

    list = fs_make();

    if(opt_bites & opt_debug)
        printf("Starting at %s\n", root);

    if (pid != 0)
    {
        printf("Сканирование запущено:\n");
        if (opt_bites & opt_active) printf("Внимание! Программа работает в активном режиме!\n\n");
        else printf("\n");
    }

    walk(list, root);

    if (opt_bites ^ opt_monothr && pid != 0)
    {
        unsigned int i = 0;
        while(i < _LITE_SYS_FORKS && pid != 0)
        {
            fork_counter++;
            pid = fork();
            if (pid == -1)
                perror(strerror(errno));
            if (pid != 0)
                ++i;
        }
    }
    if (pid == -1)
    {
        perror(strerror(errno));
    }

    fork_range = list->f_size / (_LITE_SYS_FORKS + 1); // +1 наш PARENT процесс
    fork_remainder = list->f_size % (_LITE_SYS_FORKS + 1);

    if (opt_bites ^ opt_monothr)
    {
        if (pid != 0)
            scan(list, 0, fork_range - 1);
        if (pid == 0)
        {
            unsigned int ptr_from, ptr_to;
            if (fork_counter == _LITE_SYS_FORKS)
            {
                ptr_from = fork_range * fork_counter;
                ptr_to = fork_range * (fork_counter + 1) - 1 + fork_remainder; // Сканируем всё что осталось
                scan(list, ptr_from, ptr_to);
            }
            else
            {
                ptr_from = fork_range * fork_counter;
                ptr_to = fork_range * (fork_counter + 1) - 1;
                scan(list, ptr_from, ptr_to); // 1 2 3 | 4 5 6 | 7 8 9 10 - 1 2 3 берёт paren
            }
        }
    }
    else
    {
        scan(list, 0, list->size);
    }

    if (pid == 0)
        return 0;

    // ======================= Рекурсивный поиск в директориях

    if (pid != 0)
    {

    /*
     * Таймер
    */

    if(opt_bites & opt_debug)
    {
        clock_status = clock_gettime(CLOCK_REALTIME, &stop);
        long double res_sec = (stop.tv_sec - start.tv_sec) * _LITE_TIMERNANOMTPL;
        long double res_nsec = stop.tv_nsec - start.tv_nsec; // * NANO_MULTIPLIER;
        long double tt = res_sec + res_nsec;
        tt = tt / _LITE_TIMERNANOMTPL;
        printf( "Processing time is %.7Lf seconds!\n", tt);
    }

    /*
     * Таймер
    */

    int *chld_status = malloc(sizeof(int));

    pid = wait(chld_status);
    if (pid == -1)
    {
        if (opt_bites & opt_debug)
            perror("[PARENT] {DEBUG} Child termination problem!");
    }

    printf("\nСканирование завершено!\n");
    printf(mess_found_files, c_occur_files);
    printf(mess_found_overall, c_occur_overall);

    }

    return 0;
}
