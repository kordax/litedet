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

static char *sec_arg;
bool arg_is_long                =   false;
bool arg_is_valid               =   false;

void handle_arg(char *argstr)
{
    switch(arg_is_long)
    {
        case true:                                                                                            // arg_longarg_list и arg_shortarg_list соответственно, определеные в файле const.h
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

    char *user = argv[1];

<<<<<<< HEAD
=======
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
>>>>>>> 266e8d11499363f1f82c7db8a09f8dc4bf4192a2
    char *root = get_real_path(user);
<<<<<<< HEAD
<<<<<<< HEAD
    puts(root);
>>>>>>> 4a45061c06b7e2a7455a5e31cf39e9757aa96f4b
=======
=======
    if (opt_bites & opt_debug)
>>>>>>> test
    printf("Starting at %s\n", root);
>>>>>>> dev

    /*
     * Таймер
    */
    struct timespec start, stop;
    int clock_status;
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

    printf("Сканирование запущено:\n");
    if (opt_bites & opt_active) printf("Внимание! Программа работает в активном режиме!\n\n");
    else printf("\n");

    fslist *files_list = fs_make();

    walk(files_list, root);
    scan(files_list);

    // ======================= Рекурсивный поиск в директориях

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

    printf("\nСканирование завершено!\n");
    printf(mess_found_files, c_occur_files);
    printf(mess_found_overall, c_occur_overall);

    return 0;
}
