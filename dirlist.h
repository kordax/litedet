#ifndef DIRLIST
#define DIRLIST
#endif // DIRLIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // opendir, closedir, readdir, rewinddir и Co.
#include <regex.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_DIRS 50
#define MAX_DIR_CHARS 50

typedef struct __dir_node {
    struct dirent* value;
    struct __dir_node* prev;
    struct __dir_node* next;
} dir_node;

typedef struct __dir_list {
    size_t size;
    dir_node* beg;
    dir_node* end;
} dir_list;

dir_list* make_dirlist()
{
    dir_list* tmp = (dir_list*) malloc(sizeof(dir_list));
    tmp->size = 0;
    tmp->end = tmp->beg = NULL;
    return tmp;
}

void dl_pushback(dir_list *dl, struct dirent* val)
{
    dir_node* tmp = (dir_node*) malloc(sizeof(dir_node));
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

void* dl_popback(dir_list *dl) {
    dir_node *next;
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

dir_list* get_dir_content(const char* dir_name)
{
    DIR* dir_ptr;
    dir_list* dl = make_dirlist();
    if ((dir_ptr = opendir(dir_name)) == NULL)
    {
        perror("Cannot open file");
        return NULL;
    }
    struct dirent *dir_entity;

    while (dir_entity = readdir(dir_ptr))
    {
        dl_pushback(dl, dir_entity);
    }

    return dl;
}
