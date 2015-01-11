#ifndef LIST_H
#define LIST_H  1

#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>

typedef struct fslist {
    size_t size;
    size_t d_size;
    size_t f_size;

    char *files[_LITE_MAX_FILES];
    char *dirs[_LITE_MAX_FILES];

} fslist;

typedef struct fsnode {

    char path[_POSIX_PATH_MAX];
    char *type;

} fsnode;

fslist* fs_make()
{
    fslist* tmp = (fslist*) malloc(sizeof(fslist));
    tmp->size = 0;

    return tmp;
}

void fs_pushback(fslist *list, fsnode *node) // Добавляем ноду с уже правильным и полным путём
{

    for (unsigned int i = 0; i < _LITE_MAX_FILES; i++) // Если это папка или файл, добавляем путь в массив списка
    {
        if(strcmp(node->type, "DIR") == 0)
        if(list->dirs[i] == NULL)
        {
            list->dirs[i] = (char*) malloc(_POSIX_PATH_MAX);
            //list->dirs[i] = tmp->path; //0.0008144
            strcpy(list->dirs[i], node->path);
            list->d_size++;
            break;
        }
        if(strcmp(node->type, "FIL") == 0)
        if(list->files[i] == NULL)
        {
            list->files[i] = (char*) malloc(_POSIX_PATH_MAX);
            //list->files[i] = tmp->path;
            strcpy(list->files[i], node->path);
            list->f_size++;
            break;
        }
    }

    list->size = list->f_size + list->d_size;
}
#endif // LIST_H
