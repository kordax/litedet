#ifndef SCAN
#define SCAN

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <error.h>
#include "preload.h"
#include "walk.h"

static int          current_fd;
static struct stat  current_stats;

typedef struct sigtype {

    char content[_LITE_MAX_SIGNSIZE + 1]; // +1 для '\0'
    char type[5];
    unsigned int size;

} sigtype;

void sign_rem(char *ptr_at_sig, unsigned int sig_size)
{
    memcpy(ptr_at_sig, ptr_at_sig + sig_size, strlen(ptr_at_sig) - sig_size);
    ftruncate(current_fd, current_stats.st_size - sig_size); // Меняем размер файла до нужного, т.е. сжимаем его до реаьного размера из которого исключена сигнатура
    return;
}

sigtype* sign_get()
{
    sigtype *signature = malloc(sizeof(sigtype));

    while(sign_get_sigfile_ptr[c_mark] != '[' && sign_get_sigfile_ptr[c_mark + 1] != '#') // Ищем открывающий тег
    {
        c_mark++;
    }
    char *line = sign_get_sigfile_ptr + c_mark;
    for (int i = 0; i < _LITE_KNOWN_FILETYPES; i++)
    {
        char *result = strstr(line, sys_file_types[i]);
        if (result != NULL)
        {
            if (result[5] != 63 && result[6] != 63 && opt_bites & opt_debug)
            {
                printf("Wrong open tag in base signatures at c_mark %d", c_mark);
                perror("Closing program!");
            }
            if (result[5] == '?')   // [#js#?5]
            {
                strcpy(signature->type, sys_file_types[i]);
                c_mark += 5;
                break;
            }
            else
            {
                strcpy(signature->type, sys_file_types[i]);
                c_mark += 6;        // [#php#?5] Здесь '?' шестой по счёту, двигаемся сразу сюда.
                break;
            }
        }
        else
        {
            return NULL;
        }
    }
    unsigned int i = 0;
    while(sign_get_sigfile_ptr[c_mark] != ']') // Считываем размер [#php#?5]
    {
        if(sign_get_sigfile_ptr[c_mark] == '?')
        {
            c_mark++; // Пропускаем '?'
            sign_get_sign_size[i] = sign_get_sigfile_ptr[c_mark]; // беда
            i++;
        }
        c_mark++;
    }
    signature->size = atoi(sign_get_sign_size);
    c_mark += 2; // Попадаем на ']' и перешагиваем его + перешагиваем пробел до сигнатуры (создан для удосбтва)

    strncpy(signature->content, sign_get_sigfile_ptr + c_mark, signature->size);
    signature->content[signature->size] = '\0'; // Обрезаем лишнюю память
    return signature;
}

char* scanpat(char *file)
{
    char *substr = NULL;
    char *lastfound = NULL;
    c_mark = 0;
    bool sign_found = false;
    sigtype *signature;

    while((signature = sign_get()) != NULL)
    {
        substr = strstr(file, signature->content);
        if (substr != NULL)
        {
            lastfound = malloc(strlen(substr));
            strcpy(lastfound, substr);
            sign_found = true;
            c_occur_overall++;
            if (opt_bites & opt_active)
                sign_rem(substr, signature->size);
        }
    }
    if (lastfound == NULL && !sign_found) return NULL;
    return lastfound;
}

void scan(fslist *list)
{
    for (unsigned int i = 0; i < list->f_size; i++)
    {
        current_fd = open(list->files[i], O_RDWR);
        if (current_fd < 0)
        {
            perror(strerror(errno));
        }
        if (fstat(current_fd, &current_stats) == -1)
        {
            perror(strerror(errno));
        }
        if(current_stats.st_size > 0)
        {
            char *filebuf = mmap(0, current_stats.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, current_fd, 0);

            if (filebuf == MAP_FAILED)
            {
                perror(strerror(errno));
            }

            char *result = scanpat(filebuf);

            if (msync(filebuf, current_stats.st_size, MS_SYNC) == -1)
            {
                perror(strerror(errno));
            }

            if (result)
            {
                c_occur_files++;
                printf(mess_found_in_file, list->files[i]);
                printf(mess_found_last_sig, result);
                if(opt_bites & opt_active)
                    printf(mess_found_neutralized);
                if(opt_bites & opt_log)
                {
                    // Логирование в файл
                }
            }

            if (munmap(filebuf, current_stats.st_size) == -1)
            {
                perror(strerror(errno));
            }
            if (close(current_fd) == -1)
            {
                perror(strerror(errno));
            }
        }
    }
}
#endif // SCAN
