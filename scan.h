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

char* sign_get()
{
    char* substr;
    struct stat stats;
    int fd = open("home/k/kordax/sign.txt", O_RDONLY);
    if (fd < 0)
    {
        perror(strerror(errno));
    }
    if (fstat(fd, &stats) == -1)
    {
        perror(strerror(errno));
    }
    char *buf = (char*) malloc(sizeof(stats.st_size));
    char *ptr = buf;
    if (read(fd, buf, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    char ch1, ch2, ch3, ch4;
    u_int i = 0;
    if (stats.st_size < 4)
    {
        perror("Impossible patter size! Size is less than 4 chars!");
    }
    while (ch4 != EOF)
    {
        ch1 == buf[i];
        ch2 == buf[i+1];
        ch3 == buf[i+2];
        ch4 == buf[i+3];
        if (ch1 == ' ' && ch2 == '$' && ch3 =='#' && ch4 =='>')
        {
            break;
        }
        i++;
        ptr++;
    }

    substr = ptr;

    return substr;
}

char* seekpat(char *buf)
{
    u_int len = strlen(buf);
    char *substr = sign_get();
    char *result;

    if (buf[len - 1] == substr[len - 1])
    result = strstr(buf, substr);

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
        char *buf = (char*) malloc(sizeof(stats.st_size));
        if (read(fd, buf, stats.st_size) == -1)
        {
            perror(strerror(errno));
        }
        printf("Reading %s!\n", list->files[i]);

        char* result = seekpat(buf);

        printf("I've found %s... in ", result);
        printf("file: %s", list->files[i]);

    }
}
