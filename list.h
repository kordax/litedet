#ifndef LIST_H
#define LIST_H

#endif // LIST_H

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define MAX_SYSTEM_FILES 1000000

void arrcpy(char *dest[], char *src[])
{
    char *sizer;
    memcpy(dest, src, sizeof(src) / sizeof(sizer) );
}

typedef struct fslist {
    size_t size;
    struct fsnode *head;
    struct fsnode *tail;

} fslist;

typedef struct fsnode {

    char path[_POSIX_PATH_MAX];
    char *files[MAX_SYSTEM_FILES];
    char *dirs[MAX_SYSTEM_FILES];

    struct fsnode *next;
    struct fsnode *prev;

} fsnode;

fslist* fs_make()
{
    fslist* tmp = (fslist*) malloc(sizeof(fslist));
    tmp->size = 0;
    tmp->tail = tmp->head = NULL;
    return tmp;
}

void fs_pushback(fslist *list, fsnode* node)
{
    fsnode* tmp = (fsnode*) malloc(sizeof(fsnode));
    strcpy(tmp->path, node->path);
    strcpy(tmp->dirs, node->dirs);
    strcpy(tmp->dirs, node->dirs);

    tmp->prev = list->tail;
    if (list->tail) {
    list->tail->next = tmp;
    }
    list->tail = tmp;
    if (list->head == NULL) {
    list->head = tmp;
    }
    list->size++;
}
