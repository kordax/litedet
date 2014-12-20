#ifndef WALK_H
#define WALK_H

#endif // WALK_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

fslist* walk(char *cur_dir) // Функцию буду запускать рекурсивно.
{
    DIR* cur_dir_ptr;
    struct dirent* entry;
    fslist *list = fs_make();
    fsnode node;
    cur_dir_ptr = opendir(cur_dir);
    while (entry = readdir(cur_dir_ptr))
    {
        if(!entry->d_name[0] == ".")
        {
            if(entry->d_type == DT_REG) // Обрабатываем файл
            {
                node.
                fs_pushback(list, ); //Добавляем в список наш файл
            }
            if(entry->d_type == DT_DIR) // Обрабатываем директорию
            {
                fs_pushback(list, ); //Добавляем в список наш файл
            }
        }
    }
}
