#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

    if(strcmp(argv[1], "none") != 0 && strcmp(argv[2], "none") == 0){
        if(mkdir(argv[1], 0777) != 0){
            perror("Directory not created!\n");
            EXIT_FAILURE;
        }
    }
    else if(argv[1][0] == '-' && strcmp(argv[2], "none") != 0){
        if(strcmp(argv[1], "-m") != 0 && strcmp(argv[1], "-v") != 0){
            printf("mkdir: Invalid option: -%s\n", argv[1]);
            return 1;
        }
    }
    else if(strcmp(argv[1], "-m") == 0 && strcmp(argv[2], "none") != 0 && strcmp(argv[3], "none") != 0){
        int arg2 = atoi(argv[2]);
        if(arg2 < 0 || arg2 > 7777){
            printf("mkdir: invalid file mode: %d", arg2);
        }
        if(mkdir(argv[1], arg2) != 0){
            perror("Directory not created!");
            EXIT_FAILURE;
        }
    }
    else if(strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "none") != 0){
        int arg2 = atoi(argv[2]);
        if(mkdir(argv[1], arg2) != 0){
            perror("Directory not created!");
            EXIT_FAILURE;
        }
        else{
            printf("%s\n", argv[2]);
        }
    }
}