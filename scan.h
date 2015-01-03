#ifndef SCAN
#define SCAN

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <error.h>
#include "walk.h"

static unsigned int c_mark          =   0;
static unsigned int c_occur_files   =   0;
static unsigned int c_occur_overall =   0;

char* sign_get()
{
    char *substr;
    struct stat stats;
    unsigned int signsize = 0;
    char *sigfile = "/home/kordax/sign.txt";
    int fd = open(sigfile, O_RDONLY);
    if (fd < 0)
    {
        perror(strerror(errno));
    }
    if (fstat(fd, &stats) == -1)
    {
        perror(strerror(errno));
    }
    if (c_mark > stats.st_size)
    {
        return NULL;
    }

    char *filebuf = (char *) malloc(stats.st_size);
    char buf[_LITE_MAX_SIGNSIZE] = {0};
    int i = 0;

    if (read(fd, filebuf, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    char temp[200] = {0};
    strcpy(temp, filebuf);
    if (stats.st_size < 4)
    {
        perror("Signature base is less than 4 symbols!");
    }
    while((filebuf[c_mark] != '[' || filebuf[c_mark + 1] != '#' || filebuf[c_mark + 2] != ']' || filebuf[c_mark + 3] != ' ') && filebuf[c_mark + 3] != '\0')
    {
       c_mark++;
    }
    if(filebuf[c_mark + 3] == '\0')
    {
        return NULL;
    }
    if(filebuf[c_mark] == '[' && filebuf[c_mark + 1] == '#' && filebuf[c_mark + 2] == ']' && filebuf[c_mark + 3] == ' ')
    {
        c_mark += 4;
        while(filebuf[c_mark] != ' ' && filebuf[c_mark + 1] != '$' && filebuf[c_mark + 2] != '#' && filebuf[c_mark + 3] != '>')
        {
            buf[i] = filebuf[c_mark];
            i++;
            c_mark++;
            signsize++;
        }
    }
    substr = buf;

    return substr;
}

char* scanpat(char *file)
{
    char *sign = NULL;
    char *substr = NULL;
    char *lastfound = NULL;
    c_mark = 0;
    bool sign_found = false;

    while((sign = sign_get()) != NULL)
    {
        substr = strstr(file, sign);
        if (substr != NULL)
        {
            lastfound = malloc(strlen(substr));
            strcpy(lastfound, substr);
            sign_found = true;
            c_occur_overall++;
            if (opt_bites & opt_active)
                for (unsigned int i = 0; i < strlen(sign); i++)
                    substr[i] = 'B';
        }
    }
    if (lastfound == NULL && !sign_found) return NULL;
    return lastfound;
}

void scan(fslist *list)
{
    struct stat stats;
    int fd;

    for (unsigned int i = 0; i < list->f_size; i++)
    {
        fd = open(list->files[i], O_RDWR);
        if (fd < 0)
        {
            perror(strerror(errno));
        }
        if (fstat(fd, &stats) == -1)
        {
            perror(strerror(errno));
        }
        if(stats.st_size > 0)
        {
            char *filebuf = mmap(0, stats.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

            if (filebuf == MAP_FAILED)
            {
                perror(strerror(errno));
            }

            char *result = scanpat(filebuf);

            if (msync(filebuf, stats.st_size, MS_SYNC) == -1)
            {
                perror(strerror(errno));
            }

            if (result)
            {
                c_occur_files++;
                printf("Совпадение с базой сигнатур в файле: %50s\n", list->files[i]);
                printf("    ↳ Пример последней найденной сигнатуры: %43.8s\n", result);
                if(opt_bites & opt_active)
                    printf("...Вредоносный код удалён.\n");
                if(opt_bites & opt_log)
                {
                    // Логирование в файл
                }
            }

            if (munmap(filebuf, stats.st_size) == -1)
            {
                perror(strerror(errno));
            }
            if (close(fd) == -1)
            {
                perror(strerror(errno));
            }
        }
    }
}
#endif // SCAN
