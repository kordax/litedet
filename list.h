#ifndef LIST_H
#define LIST_H  1

#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>

#endif // LIST_H

#define _MAX_SYSTEM_FILES 100000

typedef struct fslist {
    size_t size;
    size_t d_size;
    size_t f_size;
    struct fsnode *head;
    struct fsnode *tail;

    char *files[_MAX_SYSTEM_FILES];
    char *dirs[_MAX_SYSTEM_FILES];

} fslist;

typedef struct fsnode {

    char path[_POSIX_PATH_MAX];
    char *type;

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

    for (unsigned int i = 0; i <= sizeof(list->dirs); i++) // Если это папка или файл, добавляем путь в массив списка
    {
        if(strcmp(node->type, "DIR") == 0)
        if(list->dirs[i] == NULL)
        {
            list->dirs[i] = tmp->path;
            list->d_size++;
            break;
        }
        if(strcmp(node->type, "FIL") == 0)
        if(list->files[i] == NULL)
        {
            //list->dirs[i] = (char*) malloc(sizeof(char *[_POSIX_PATH_MAX])); // Создаём массив char'ов (т.е. строку), чтобы можно было захуярить туда чего-нибудь ;)
            list->files[i] = tmp->path;
            list->f_size++;
            break;
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
