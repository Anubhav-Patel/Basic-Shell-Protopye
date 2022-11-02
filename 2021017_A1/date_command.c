#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    char* date_time;
    time_t t;
    time(&t);

    if(strcmp(argv[1], "none") == 0 && strcmp(argv[2], "none") == 0){
        date_time = ctime(&t);
        for(int i = 0; i < strlen(date_time)-1; i++){
            printf("%c", date_time[i]);
        }
        printf(" IST                                                                                                                                ");
    }

    if(argv[1][0] == '-'){
        if(strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-r") != 0){
            printf("date: Invalid option: -%s", argv[1]);
            return 0;
        }
    }

    if(strcmp(argv[1], "none") != 0 && argv[2][0] == '-'){
        if(strcmp(argv[2], "-u") != 0 && strcmp(argv[2], "-r") != 0){
            printf("date: Invalid option: -%s", argv[2]);
            return 0;
        }
    }

    if(strcmp(argv[1], "-u") == 0 && strcmp(argv[2], "none") == 0){
        t = t - 19800;
        date_time = ctime(&t);
        for(int i = 0; i < strlen(date_time)-1; i++){
            printf("%c", date_time[i]);
        }
        printf(" UTC                                                                                                                                ");
    }

    if(strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "none") != 0){
        struct stat filestat;
        stat(argv[2], &filestat);
        printf("%s", ctime(&filestat.st_mtime));
    }

    if(strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "none") == 0){
        printf("date: option requires an argument --r");
        // printf("\n");
    }
    return 1;

}