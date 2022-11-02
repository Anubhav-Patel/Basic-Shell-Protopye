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
    if(strcmp(argv[1], "none") == 0 && strcmp(argv[2], "none") == 0){
        printf("Please provide a file");
    }
    if(argv[1][0] == '-' && strcmp(argv[2], "none") != 0){
        if(strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-f") != 0){
            printf("rm: Invalid option: -%s\n", argv[1]);
            return 1;
        }
    }
    if(strcmp(argv[1], "none") != 0 && strcmp(argv[2], "none") == 0){
        if(remove(argv[1]) != 0){
            printf("rm: %s: No such file or directory\n", argv[1]);
        }
    }
    if(strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "none") != 0){
        if(remove(argv[2]) != 0){
            perror("rm: \n");
        }
        else{
            printf("%s", argv[2]);
            printf("\n");
        }
    }
    if(strcmp(argv[1], "-f") == 0 && strcmp(argv[2], "none") != 0){
        remove(argv[2]);
    }
}