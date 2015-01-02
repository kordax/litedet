#ifndef WALK_H
#define WALK_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include "list.h"
#include <errno.h>
#include <error.h>

void walk(fslist* list, char *root) // Функцию буду запускать рекурсивно.
{
    DIR* cur_dir_ptr;
    struct dirent* entry;
    fsnode *node = (fsnode*) malloc(sizeof(fsnode));
    cur_dir_ptr = opendir(root);
    if(cur_dir_ptr == NULL)
    {
        if(errno == EACCES) perror(strerror(EACCES));
        if(errno == ENOTDIR) perror(strerror(ENOTDIR));
        if(errno == EBADF) perror(strerror(EBADF));
        if(errno == EMFILE) perror(strerror(EMFILE));
        if(errno == ENFILE) perror(strerror(ENFILE));
        if(errno == ENOENT) perror(strerror(ENOENT));
        if(errno == ENOMEM) perror(strerror(ENOMEM));
    }
    while ((entry = readdir(cur_dir_ptr)) != NULL)
    {
        if(errno == EBADF) perror(strerror(EBADF));
        char temp[_POSIX_PATH_MAX] = {0};
        strcpy(temp, root);
        if(entry->d_name[0] != 46)
        {
            if(entry->d_type == DT_REG) // Обрабатываем файл
            {
                node->type = "FIL";
                strcat(temp, "/");
                strcpy(node->path, strcat(temp, entry->d_name));
                fs_pushback(list, node); //Добавляем в список наш файл
                puts(node->path);
            }
            if(entry->d_type == DT_DIR) // Обрабатываем директорию
            {
                node->type = "DIR";
                strcat(temp, "/");
                strcat(temp, entry->d_name);
                strcpy(node->path, temp);
                fs_pushback(list, node); //Добавляем в список наш файл
                puts(node->path);
                walk(list, temp);
            }
        }
    }

    closedir(cur_dir_ptr);
    return;
}
#endif // WALK_H
