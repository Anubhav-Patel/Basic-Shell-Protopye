#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <fcntl.h>
#define DELIMITERS " \t\r\n\a"



char* readLine(){
    char* string = malloc(sizeof(char) * 10240);     //allocating memory to the character array       

    if(!string){
        printf("Cannot allocate memory!");
        exit(EXIT_FAILURE);
    }

    int charac;         //getchar returns integer value of ascii characters
    int index = 0;
    
    while(1){
        charac = getchar();           //get single char

        if(charac == EOF || charac == '\n'){    //if c = EOF or newline, put \0 and return the string
            string[index] = '\0';
            return string;
        }
        else{
            string[index] = charac;        //add the character to the array of characters
        }
        index++;
    }

    if(index >= 10240){
        printf("Memory limit exceeded!");
        exit(EXIT_FAILURE);
    }
}

int numOfArgs = 0;
char **getArgs(char* string){
    char *tokenPointer;                                     //points to string(array of characters)
    char **token_list = malloc(sizeof(char*) * 256);        //array for storing pointers pointing to the (pointer of array of characters i.e. strings)

    if(!token_list){
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    tokenPointer = strtok(string, DELIMITERS);             //https://www.tutorialspoint.com/string-tokenisation-function-in-c
    while(tokenPointer != NULL){
        token_list[index] = tokenPointer;
        tokenPointer = strtok(NULL, DELIMITERS);
        index++;
    }
    numOfArgs= index;
    return token_list;
}

int flag = 0;
int cat_command(char* arg1, char* arg2){
    char *input;
    char **in;

    if(strcmp(arg1, "none") == 0 && strcmp(arg2, "none") == 0){
        // flag = 1;
        input = readLine();             //reads the input line
        in = getArgs(input);            //breaks the line into arguments
        int i = 0;
        while(in[i] != NULL){
            fputs(in[i], stdout);
            fputs(" ", stdout);
            i++;
        }
        printf("\n");
        cat_command(arg1, arg2);     //loops if not given any file as argument
    }

    if(arg1[0] == '-' && strcmp(arg2, "none") != 0){
        if(strcmp(arg1, "-s") != 0 && strcmp(arg1, "-n") != 0){
            printf("cat: Invalid option: -%s\n", arg1);
            return 1;
        }
    }

    if(arg1[0] == '-' && strcmp(arg2, "none") == 0){
        if(strcmp(arg1, "-s") != 0 && strcmp(arg1, "-n") != 0){
            printf("cat: Invalid option: -%s\n", arg1);
            return 1;
        }
        else{
            input = readLine();             //reads the input line
            in = getArgs(input);            //breaks the line into arguments
            int i = 0;
            while(in[i] != NULL){
                fputs(in[i], stdout);
                fputs(" ", stdout);
                i++;
            }
            printf("\n");
            cat_command(arg1, arg2);     //loops if not given any file as argument
        }
    }

    if(strcmp(arg1, "none") != 0 && strcmp(arg2, "none") == 0){
        char *buffer = malloc(sizeof(char) * 1024);
        const char *filename = arg1;
        int file_descriptor = open(filename, O_RDONLY);
        if(file_descriptor < 0){
            printf("cat: No such file or directory");
            printf("\n");
        }
        else{
            read(file_descriptor, buffer, 102400);
            printf("%s", buffer);
            printf("\n");
            close(file_descriptor);
        }
        return 1;
    }

    if(strcmp(arg1, "-s") == 0  && strcmp(arg2, "none") != 0){
        // printf("xx2");
        // printf("%s", arg2);
        char *buffer = malloc(sizeof(char) * 1024);
        const char *filename = arg2;
        int file_descriptor = open(filename, O_RDONLY);
        if(file_descriptor < 0){
            printf("cat: No such file or directory");
            // printf("\n");
        }
        else{
            read(file_descriptor, buffer, 102400);
            for(int i = 0; i < strlen(buffer); i++){
                printf("%c", buffer[i]);
                if(buffer[i] == '\n' && buffer[i+1] == '\n'){
                    while(buffer[i] == '\n'){
                        i++;
                    }
                    printf("\n");
                    i--;
                }
                
            }
            close(file_descriptor);
        }
        // printf("\n");
        return 1;
    }

    if(strcmp(arg1, "-n") == 0  && strcmp(arg2, "none") != 0){
        char *buffer = malloc(sizeof(char) * 1024);
        const char *filename = arg2;
        int file_descriptor = open(filename, O_RDONLY);
        if(file_descriptor < 0){
            printf("cat: No such file or directory");
            // printf("\n");
        }
        else{
            int j = 2;
            printf("1 ");
            read(file_descriptor, buffer, 102400);
            for(int i = 0; i < strlen(buffer)-1; i++){
                printf("%c", buffer[i]);
                if(buffer[i] == '\n'){
                    printf("%d ", j);
                    j++;
                }
            }
            // printf("\n");
            close(file_descriptor);
        }
        return 1;
    }


    if(strcmp(arg1, "none") != 0  && strcmp(arg2, "-s") == 0){
        char *buffer = malloc(sizeof(char) * 1024);
        const char *filename = arg1;
        int file_descriptor = open(filename, O_RDONLY);
        if(file_descriptor < 0){
            printf("cat: No such file or directory");
            // printf("\n");
        }
        else{
            read(file_descriptor, buffer, 102400);
            printf("%s", buffer);
            printf("\n");
            close(file_descriptor);
        }
        return 1;
    }

    if(strcmp(arg1, "none") != 0  && strcmp(arg2, "-n") == 0){
        char *buffer = malloc(sizeof(char) * 1024);
        const char *filename = arg1;
        int file_descriptor = open(filename, O_RDONLY);
        if(file_descriptor < 0){
            printf("cat: No such file or directory");
            // printf("\n");
        }
        else{
            read(file_descriptor, buffer, 102400);
            printf("%s", buffer);
            // printf("\n");
            close(file_descriptor);
        }
        return 1;
    }   
    return 1;
}

int main(int argc, char* argv[]){
    cat_command(argv[1], argv[2]);
    return 0;
}