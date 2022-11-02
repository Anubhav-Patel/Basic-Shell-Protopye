#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/syscall.h>
#include <dirent.h>

int ls_command(char *one, char *two){
    struct dirent *d;
    DIR *dir = opendir(".");
    if(!dir){
        perror("Can't open directory.");
        exit(EXIT_FAILURE);
    }
    if(one[0] == '-' && strcmp(two, "none") == 0){
        if(strcmp(one, "-a") != 0 && strcmp(one, "-m") != 0){
            printf("ls: Invalid option: -%s\n", one);
            return 1;
        }
    }
    if(strcmp(one , "none") != 0 && two[0] == '-'){
        if(strcmp(two, "-a") != 0 && strcmp(two, "-m") != 0){
            printf("ls: Invalid option: -%s\n", two);
            return 1;
        }
    }
    
    if(strcmp(one, "-a") == 0 && strcmp(two, "none") == 0){
        while((d = readdir(dir)) != NULL){
            printf("%s", d->d_name);
            printf("\t");
        }
        return 1;
    }
    if(strcmp(one, "-m") == 0 && strcmp(two, "none") == 0){
        while((d = readdir(dir)) != NULL){
            if(d->d_name[0] != '.'){
                printf("%s", d->d_name);
                printf(", ");
            }
        }
        return 1;
    }
    if((strcmp(one, "-a") == 0 && strcmp(two, "-m") == 0) || strcmp(one, "-m") == 0 && strcmp(two, "-a") == 0){
        while((d = readdir(dir)) != NULL){
                printf("%s", d->d_name);
                printf(", ");
        }
        return 1;
    }
    if(strcmp(one, "-a") != 0 && strcmp(one, "-m") != 0 && strcmp(one, "none") != 0 && strcmp(two, "none") == 0){
        DIR *dir1 = opendir(one);
        if(!dir1){
            perror("Can't open directory.");
            exit(EXIT_FAILURE);
        }
        while((d = readdir(dir1)) != NULL){
                if(d->d_name[0] != '.'){
                    printf("%s", d->d_name);
                    printf("\t");
            }
        }
        return 1;
    }
    if(strcmp(one, "-a") == 0 && strcmp(two, "none") != 0 && strcmp(two, "-m") != 0 && strcmp(two, "-a") != 0){
        DIR *dir1 = opendir(two);
        if(!dir1){
            perror("Can't open directory.");
            exit(EXIT_FAILURE);
        }
        while((d = readdir(dir1)) != NULL){
            printf("%s", d->d_name);
            printf("\t");
        }
        return 1;
    }
    if(strcmp(one, "-m") == 0 && strcmp(two, "none") != 0 && strcmp(two, "-m") != 0 && strcmp(two, "-a") != 0){
        DIR *dir1 = opendir(two);
        if(!dir1){
            perror("Can't open directory.");
            exit(EXIT_FAILURE);
        }
        while((d = readdir(dir1)) != NULL){
            if(d->d_name[0] != '.'){
                printf("%s", d->d_name);
                printf(", ");
            }
        }
        return 1;
    }
    if(strcmp(one, "none") == 0 && strcmp(two, "none") == 0){
        while((d = readdir(dir)) != NULL){
            if(d->d_name[0] != '.'){
                printf("%s", d->d_name);
                printf("\t");
            }
        }
        return 1;
    }
    else{
        printf("No such File or Directory");
    }
    printf("\n");
    return 1;
}

int main(int argc, char *argv[]){
    ls_command(argv[1], argv[2]);
    return 0;
}

