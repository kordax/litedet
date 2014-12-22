#ifndef SCAN
#define SCAN

#endif // SCAN

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <error.h>
#include "walk.h"

void scan(fslist *list)
{
    struct stat stats;
    for (unsigned int i = 0;i < list->f_size; i++)
    {
        FILE *fptr;
        ssize_t fsz, bufsz;
        //int fd = open(list->files[i], O_RDONLY);
        fptr = fopen(list->files[i], "r");

        /*if (fd == -1)
        {
            perror(strerror(errno));
        }
        if (fstat(fd, stats) == -1)
        {
            perror(strerror(errno));
        }*/
        if (stat(list->files[i], &stats) == -1)
        {
            perror(strerror(errno));
        }
        printf("Reading %s!\n", list->files[i]);
        char buf[stats.st_size];
        fsz = getline(&buf, bufsz, fptr);
    }
}
