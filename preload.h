#ifndef PRELOAD_H
#define PRELOAD_H

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

// scan.h

static char *sign_get_sigfile_ptr;
static char *sign_get_sign_size;
static unsigned int c_mark          =   0;
static unsigned int c_occur_files   =   0;
static unsigned int c_occur_overall =   0;

int preload_buffers()
{
    sign_get_sign_size = (char *) malloc(5);
    if (errno == 0)
        return 0;
    else
        return -1;
}

int preload()
{
    if (preload_buffers() < 0)
    {
        perror("Ошибка в preload_buffers()");
    }

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
    if (c_mark > stats.st_size)
    {
        return -1;
    }

    sign_get_sigfile_ptr = (char *) malloc(stats.st_size);
    if (read(fd, sign_get_sigfile_ptr, stats.st_size) == -1)
    {
        perror(strerror(errno));
    }
    if (stats.st_size < 4)
    {
        perror("Signature base is less than 4 symbols!");
    }

    return 0;
}

#endif // PRELOAD_H
