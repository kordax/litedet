#ifndef WALK_H
#define WALK_H

#endif // WALK_H

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "list.h"

fslist* walk(char *cur_dir)
{
    DIR* cur_dir_ptr;
    struct dirent* entry;
    fslist list = fs_make();
    fsnode node;
    cur_dir_ptr = opendir(cur_dir);
    while (entry = readdir(cur_dir_ptr))
    {
        if(!entry->d_name[0] == ".")
        {
            if(entry->d_type == DT_REG) fs_pushback(list, ); //Добавляем в список наш файл
        }
    }
}
