#ifndef SCAN
#define SCAN

#endif // SCAN

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

int scan_pat(char *string)
{
    for (int i = 0; i < sizeof(string) / sizeof(char); i++)
    {

    }
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
        if ((addr = mmap(0, stats.st_size, PROT_READ, MAP_PRIVATE, fd, 0) == MAP_FAILED))
        {
            perror(strerror(errno));
        }
        //char *buf = (char*) malloc(sizeof(char[stats.st_size]));
        char buf[stats.st_size];
        if (read(fd, buf, stats.st_size) == -1)
        {
            perror(strerror(errno));
        }
        printf("Reading %s!\n", list->files[i]);

    }
}
