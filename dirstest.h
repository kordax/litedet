#ifndef DIRSTEST
#define DIRSTEST

#endif // DIRSTEST

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
//argv[1] - директория
//argv[2] - файл протокола
{
    if ((argc<2) || (argc>3))
    {
        printf("2 or 3 parameters required\n");
        return -1;
    }
    else
    {
        int fd;
        if (!(fd=open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666)))
        {
            printf("Can\'t create file\n");
            return -1;
        }
        else
        {
            DIR *dir;
            if ((dir=opendir(argv[1]))==NULL)
            {
                printf("Can\'t open folder\n");
                return -1;
            }
            else
            {
                struct dirent *f_cur;
                while ((f_cur=readdir(dir))!=NULL)
                {
                    if (argc==3)
                    {
                        int i=0;
                        for (i=0; i<strlen(f_cur->d_name); ++i) write(fd, &f_cur->d_name[i], 1);
                        write(fd, "\n", 1);
                    }
                    else printf("%s\n", f_cur->d_name);
                }
                printf("Done...\n");
                close(fd);
                closedir(dir);
                return 0;
            }
        }
    }
}
