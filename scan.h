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
    struct stat stats;
    int fd = open("home/k/kordax/test/sign.txt", O_RDONLY);
    if (fd < 0)
    {
        perror(strerror(errno));
    }
    if (fstat(fd, &stats) == -1)
    {
        perror(strerror(errno));
    }
    char *buf = (char*) malloc(sizeof(stats.st_size));
    if (read(fd, buf, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    char ch1, ch2, ch3;
    u_int i = 0;
    while (ch3 != EOF)
    {
        ch1 == buf[i];
        ch2 == buf[i+1];
        ch3 == buf[i+2];
        if (ch1 != '$' && ch2 !='#' && ch3 !='>')
        {

        }
        i++;
    }

    return;
}

int seekpat(char *string)
{
    u_int len = strlen(string);
    if (string[len - 1] == buf[len - 1])
    strstr(buf, );
    return 0;
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


    }
}
