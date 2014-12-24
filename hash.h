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

#define _MD5_APPEND_BITS 0x80
#define _SIGN_MAX_SIZE 8192

int gen_hash(char *input)
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

    N = size - 448 / 512; // L = 512*N+448

    length = 512 * N + 448;

    return 0;
}
