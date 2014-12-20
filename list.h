#ifndef LIST_H
#define LIST_H

#endif // LIST_H

#include <string.h>
#include <dirent.h>
#include <limits.h>


#define _MAX_SYSTEM_FILES 100000

void arrcpy(char *dest[], char *src[])
{
    char *sizer;
    memcpy(dest, src, sizeof(src) / sizeof(sizer) );
}

typedef struct fslist {
    size_t size;
    struct fsnode *head;
    struct fsnode *tail;

    char *files[_MAX_SYSTEM_FILES];
    char *dirs[_MAX_SYSTEM_FILES];

} fslist;

typedef struct fsnode {

    char path[_POSIX_PATH_MAX];
    char type[3];

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

void fs_pushback(fslist *list, fsnode *node) // Добавляем ноду с уже правильным и полным путём
{
    fsnode* tmp = (fsnode*) malloc(sizeof(fsnode));
    strcpy(tmp->path, node->path);

    for (int i = 0; i <= sizeof(list->dirs); i++) // Если это папка или файл, добавляем путь в массив списка
    {
        if(node->type == "DIR")
        if(list->dirs[i] == NULL)
        {
            list->dirs[i] = tmp->path;
        }
        if(node->type == "FILE")
        if(list->files[i] == NULL)
        {
            list->files[i] = tmp->path;
        }
    }

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
