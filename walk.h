#ifndef WALK_H
#define WALK_H

#endif // WALK_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include "list.h"

void walk(fslist* list, char *root) // Функцию буду запускать рекурсивно.
{
    DIR* cur_dir_ptr;
    struct dirent* entry;
    fsnode *node = (fsnode*) malloc(sizeof(node));
    cur_dir_ptr = opendir(root);
    if(cur_dir_ptr == NULL) printf("Cannot open %s!", root);
    while (entry = readdir(cur_dir_ptr))
    {
        if(entry->d_name[0] != 46)
        {
            if(entry->d_type == DT_REG) // Обрабатываем файл
            {
                node->type = "FIL";
                //strcpy(current, root);
                strcat(root, "/");
                strcpy(node->path, strcat(root, entry->d_name));
                fs_pushback(list, node); //Добавляем в список наш файл
                puts(node->path);
            }
            if(entry->d_type == DT_DIR) // Обрабатываем директорию
            {
                node->type = "DIR";
                //strcpy(current, root);
                strcat(root, "/");
                strcpy(node->path, strcat(root, entry->d_name));
                fs_pushback(list, node); //Добавляем в список наш файл
                puts(node->path);
                walk(list, root);
            }
        }
    }

    closedir(cur_dir_ptr);

    return list;
}
