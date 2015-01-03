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

char* sign_get()
{
    char *substr;
    struct stat stats;
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
    if (con_mark > stats.st_size)
    {
        return NULL;
    }
    char buf[_LITE_MAX_SIGNSIZE] = {0};
    char *ptr;
    if (read(fd, buf, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    char ch1, ch2, ch3, ch4;
    unsigned int i = 0;
    unsigned int tmplin = 0;
    size_t ptn_size = 3;
    if (stats.st_size < 4 && opt_bites & opt_debug)
    {
        perror("Signature base is less than 4 symbols!");
    }
    while (ch4 != EOF)
    {
        ptn_size++;
        ch1 = buf[i];
        ch2 = buf[i+1];
        ch3 = buf[i+2];
        ch4 = buf[i+3];
        if (ch1 == '\n')
        {
            tmplin++; // Идентифицируем строку
        }
        if (ch1 == ' ' && ch2 == '$' && ch3 =='#' && ch4 =='>')
        {
            ptr = (char*) malloc(ptn_size);
            memcpy(ptr, buf, ptn_size); // Копируем найденную строку, за исключением закрывающих тегов!
            ptr[ptn_size - 4] = '\0'; // Добавляем 0\ вконец. Конец у нас - 4, т.к. по факту имеем пробел(_) и $#>
            break;
        }
        con_mark++;
        i++;
    }
    if (ch4 == EOF && opt_bites & opt_debug)
    {
        printf("Missing $#> tag on %d line \n", tmplin);
        perror("Cannot proceed! Fatal error!");
    }

    substr = ptr;

    return substr;
}

int scanpat(char *file)
{
    char *sign;
    char *substr;

    while((sign = sign_get()) != NULL)
    {
        substr = strstr(file, sign);
        if (substr != NULL)
        {
            con_equal++;
            fflush(stdout);
            if (opt_bites & opt_active)
                for (unsigned int i = 0; i < strlen(sign); i++)
                    substr[i] = 'B';
        }
    }
    if (substr == NULL) return -1;
    return 0;
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
            char *fileptr = mmap(0, stats.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

            if (fileptr == MAP_FAILED)
            {
                perror(strerror(errno));
            }

            int result = scanpat(fileptr);

            if (msync(fileptr, stats.st_size, MS_SYNC) == -1)
            {
                perror(strerror(errno));
            }

            if (result)
            {
                printf("Совпадение с базой сигнатур в файле: %s\n", list->files[i]);
                if(opt_bites & opt_active)
                    printf("...Вредоносный код удалён.\n");
                if(opt_bites & opt_log)
                {
                    // Логирование в файл
                }
            }

            if (munmap(fileptr, stats.st_size) == -1)
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
