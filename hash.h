#ifndef HASH_H
#define HASH_H

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

#endif // HASH_H

#define _APPEND_BIT 0x80
#define _ZERO_BIT 0x00
#define _SIGN_MAX_SIZE 8192

int md5_append(char *input)
{
    unsigned int size = 0;
    unsigned int i = 0;
    unsigned int N = 0;
    unsigned int length;
    while(input[i] != NULL)
    {
        i++;
        size++;
    }
    if (size == 0) return -1;

    while (size % 512 != 448 % 512)
    {

    }

    return 0;
}
