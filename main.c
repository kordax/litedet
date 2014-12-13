#include "includes.h"
#include <time.h>

#define NANO_MULTIPLIER 1000000000

int main(int argc, char *argv[])
{
    struct timespec start, stop;
    int clock_status = clock_gettime(CLOCK_REALTIME, &start);
    if (clock_status < 0)
    {
        perror("Timer error");
        return 1;
    }

    char dir_prefix[] = "/media/kordax/7c1bb3dc-12a8-46d6-b140-58c8a60fff94/";
    char dir_append[32];
    char dir_name[sizeof(dir_prefix) + 34] = {0};

    scanf("%s", dir_append);
    //if(strlen(dir_append) > sizeof)

    strcat(dir_name, dir_prefix);
    strcat(dir_name, dir_append);

    puts(dir_name);

    DIR* dirptr;
    if ((dirptr = opendir(dir_name)) == NULL)
    {
        perror("Cannot open file");
        return 1;
    }
    struct dirent *dire = readdir(dirptr);

    puts(dire->d_name);

    clock_status = clock_gettime(CLOCK_REALTIME, &stop);
    long double res_sec = (stop.tv_sec - start.tv_sec) * NANO_MULTIPLIER;
    long double res_nsec = stop.tv_nsec - start.tv_nsec;// * NANO_MULTIPLIER;
    long double tt = res_sec + res_nsec;
    tt = tt / 1000000000;
    printf( "Processing time is %.2Lf seconds!\n", tt);
    return 0;
}

