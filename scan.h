#ifndef SCAN
#define SCAN

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <error.h>
#include "walk.h"

#endif // SCAN

static u_int mark = 0;

char* getcharline(const char* buf)
{
    u_int i = 0;
    u_int cnt = 0;

    if(buf[mark])
    {
        return NULL;
    }

    if(buf[mark] == '\n')
    {
        mark++;
    }
    size_t size = 0;
    while (buf[mark] != '\n') // Найдём размер буфера
    {
        printf("buf[%d] ", mark);
        printf("= %c \n", buf[mark]);
        size++;
        mark++;
        cnt++;
    }

    mark -= cnt;

    char *line = (char*) malloc(size);
    while (buf[mark] != '\n') // Скопируем данные и установим маркер
    {
        line[i] = buf[mark];
        i++;
        mark++;
    }

    line[mark] = '\0';

    return line;
}

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
    char *buf = (char*) malloc(sizeof(stats.st_size));
    char *ptr;
    if (read(fd, buf, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    char ch1, ch2, ch3, ch4;
    u_int i = 0;
    u_int line = 0;
    size_t ptn_size = 3;
    if (stats.st_size < 4)
    {
        perror("Impossible pattern size! Size is less than 4 chars!");
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
            line++; // Идентифицируем строку
        }
        if (ch1 == ' ' && ch2 == '$' && ch3 =='#' && ch4 =='>')
        {
            ptr = (char*) malloc(ptn_size);
            memcpy(ptr, buf, ptn_size); // Копируем найденную строку, за исключением закрывающих тегов!
            ptr[ptn_size - 4] = '\0'; // Добавляем 0\ вконец. Конец у нас - 4, т.к. по факту имеем пробел(_) и $#>
            //ptr[ptn_size - 3] = (char)92; // Добавляем 0\ вконец.
            break;
        }
        i++;
    }
    if (ch4 == EOF)
    {
        printf("Missing $#> tag on %d line \n", line);
        perror("Cannot proceed! Fatal error!");
    }

    substr = ptr;

    return substr;
}

char* seekpat(const char *buf, const char *file)
{
    char *substr = sign_get();
    char *result, *line;

    u_int linenmb = 0;

    //if (buf[len - 1] == substr[len - 1])
    while((line = getcharline(buf)) != NULL)
    {
        linenmb++;
        result = strstr(line, substr);
        if(result != NULL)
        {
            printf("Found substring %s3 ", result);
            printf("on line #");
            printf("%d", linenmb);
            printf("(");
            printf("%d", mark);
            printf(")");
            printf("in file %s", file);
        }
    }
    if (result == NULL)
    {
        perror("No substr found!");
    }

    return result;
}

void scan(fslist *list)
{
    struct stat stats;
    int fd;
    void *addr;
    for (unsigned int i = 0;i < list->f_size; i++)
    {
        fd = open(list->files[i], O_RDONLY);
        if (fd < 0)
        {
            perror(strerror(errno));
        }
        if (fstat(fd, &stats) == -1)
        {
            perror(strerror(errno));
        }
        addr = mmap(0, stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if(addr == MAP_FAILED)
        {
            perror(strerror(errno));
        }
        //char *buf = (char*) malloc(sizeof(char[stats.st_size]));
        char *buf = (char*) malloc(sizeof(char[stats.st_size + 1]));
        if (read(fd, buf, stats.st_size) == -1)
        {
            perror(strerror(errno));
        }
        printf("Reading %s!\n", list->files[i]);

        char* result = seekpat(buf, list->files[i]);

        printf("I've found %s... in ", result);
        printf("file: %s", list->files[i]);

    }
}
