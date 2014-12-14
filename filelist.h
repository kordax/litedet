#ifndef FILELIST
#define FILELIST
#endif // FILELIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // opendir, closedir, readdir, rewinddir и Co.
#include <regex.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct __file_node {
    struct dirent* value;
    struct __file_node* prev;
    struct __file_node* next;
} file_node;

typedef struct __file_list {
    size_t size;
    file_node* beg;
    file_node* end;
} file_list;

file_list* make_dirlist()
{
    file_list* tmp = (file_list*) malloc(sizeof(file_list));
    tmp->size = 0;
    tmp->end = tmp->beg = NULL;
    return tmp;
}

void dl_pushback(file_list *dl, struct dirent* val)
{
    file_node* tmp = (file_node*) malloc(sizeof(file_node));
    tmp->value = val;
    tmp->prev = dl->end;
    if (dl->end) {
        dl->end->next = tmp;
    }
    dl->end = tmp;

    if (dl->beg == NULL) {
        dl->beg = tmp;
    }
    dl->size++;
}

void* dl_popback(file_list *dl) {
    file_node *next;
    char *tmp;
    if (dl->end == NULL) {
        exit(4);
    }

    next = dl->end;
    dl->end = dl->end->prev;
    if (dl->end) {
        dl->end->next = NULL;
    }
    if (next == dl->beg) {
        dl->beg = NULL;
    }
    tmp = next->value;
    free(next);

    dl->size--;
    return tmp;
}

file_list* get_dir_content(const char* dir_name)
{
    DIR* dir_ptr;
    file_list* dl = make_dirlist();
    if ((dir_ptr = opendir(dir_name)) == NULL)
    {
        return NULL;
    }
    struct dirent *dir_entity;

    while (dir_entity = readdir(dir_ptr))
    {
        dl_pushback(dl, dir_entity);
    }

    return dl;
}

file_node* dl_get(file_list* dl, size_t index) { // Получим следующий элемент

    if (index > dl->size)
        return NULL;

    file_node* tmp = dl->beg;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        if(tmp->value->d_name[0] == '.') tmp = tmp->next;
        i++;
    }

    return tmp;
}
