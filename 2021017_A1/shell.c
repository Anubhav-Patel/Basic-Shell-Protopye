#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <pthread.h>
#define DELIMITERS " \t\r\n\a"

int start(char **argument_list, char *path);
void shell_loop();

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

int cd_func(char **argument_list){

    if(argument_list[1] == NULL){   
        if(chdir("/Users/anubhav") != 0){               //chdir changes directory to user
            perror("Cannot change directory");
            printf("\n");
        }                        //when no destination directory is passed
    }
    else if(strcmp(argument_list[1], "-L") == 0 && argument_list[2] == NULL){
        if(chdir("/Users/anubhav") != 0){               //chdir changes directory to user
            perror("Cannot change directory");
            printf("\n");
        }
        else{
        
        }
    }
    else if(strcmp(argument_list[1], "-") == 0 && argument_list[2] == NULL){
        if(chdir("/Users/anubhav") != 0){               //chdir changes directory to user
            perror("Cannot change directory");
            printf("\n");
        }
        else{
            
        }
    }
    else if(strcmp(argument_list[1], "-L") == 0 && strcmp(argument_list[1], "-") == 0){
        if(chdir("/Users/anubhav") != 0){               //chdir changes directory to user
            perror("Cannot change directory");
            printf("\n");
        }
        else{
            
        }
    }
    else if(strcmp(argument_list[1], "-") == 0 && strcmp(argument_list[1], "-L") == 0){
        if(chdir("/Users/anubhav") != 0){               //chdir changes directory to user
            perror("Cannot change directory");
            printf("\n");
        }
        else{
       
        }
    }
    else{
        if(chdir(argument_list[1]) != 0){               //chdir changes directory
            perror("Cannot change directory");
            printf("\n");
        }
    }

    return 1;
}

int echo_command(char **argument_list){
    int i = 1;
    int count = 0;
    char **str_list = malloc(sizeof(char*) * 256);

    while(argument_list[i] != NULL){  
        for(int k = 0; k < strlen(argument_list[i]); k++){
            if(argument_list[i][k] == '"'){
                count++;
            }
        }
        i++;
    }
    if(count%2 == 0){
        i = 1;
        int flag = 0;
        while(argument_list[i] != NULL){  
            if(strcmp(argument_list[1], "-n") == 0){
                i++;
                flag = 1;
            }
            if(strcmp(argument_list[1], "-e") == 0){
                i = 2;
                for(int k = 0; k < strlen(argument_list[i]); k++){
                    if(argument_list[i][k] == 92 && (argument_list[i][k+1] == 't' || argument_list[i][k+1] == 'r' || argument_list[i][k+1] == 'n' || argument_list[i][k+1] == 'a')){
                        if(argument_list[i][k+1] == 't'){
                            printf("\t");
                            k++;
                        }
                        if(argument_list[i][k+1] == 'r'){
                            printf("\r");
                            k++;
                        }
                        if(argument_list[i][k+1] == 'n'){
                            printf("\n");
                            k++;
                        }
                        if(argument_list[i][k+1] == 'a'){
                            printf("\a");
                            k++;
                        }
                    }
                    else{
                        if(argument_list[i][k] != '"'){
                            printf("%c", argument_list[i][k]);
                        }
                    }
                }
                fputs(" ", stdout);
            }
            else{
                for(int k = 0; k < strlen(argument_list[i]); k++){
                    if(argument_list[i][k] != '"'){
                        printf("%c", argument_list[i][k]);
                    }
                }
                fputs(" ", stdout);
            }
            i++;
        }
        if(flag != 1){
            printf("\n");
        }
    }
    else{
        int z = 0;
        while(1==1){
            char* str  = malloc(sizeof(char) * 10240);
            int count2 = 0;
            scanf("%[^\n]%*c", str);

            for(int a = 0; a < strlen(str); a++){
                if(str[a] == '"'){
                    count2++;
                }
            }
            if(count2%2 == 0){
                str_list[z] = str;
                z++;
            }
            else{
                int i = 1;
                while(argument_list[i] != NULL){  
                    for(int k = 0; k < strlen(argument_list[i]); k++){
                        if(argument_list[i][k] != '"'){
                            printf("%c", argument_list[i][k]);
                        }
                    }
                    fputs(" ", stdout);
                    i++;
                }

                for(int n = 0; n < z; n++){
                    printf("\n");
                    for(int j = 0; j < strlen(str_list[n]); j++){
                        if(str_list[n][j] != '"'){
                            printf("%c", str_list[n][j]);
                        }
                    }
                }
                printf("\n");
                for(int j = 0; j < strlen(str); j++){
                        if(str[j] != '"'){
                            printf("%c", str[j]);
                        }
                    }
                printf("\n");
                break;
            }
        }
    }

    return 1;
}

void *thread_launch(void *argument){
    
    char** arg1 = argument;
    char * a = malloc(sizeof(char)*256);
    strcat(a, "/Users/anubhav/Documents/OS/");
    int i = 1;

    strcat(a,arg1[0]);
    strcat(a,"_command");
    strcat(a," ");
    while(strcmp(arg1[i], "&t") != 0){
        strcat(a, arg1[i]);
        
        strcat(a, " ");
        i++;
    }
    for(int i=0;i<3;i++){
        strcat(a,"none");
        strcat(a," ");
    }
    printf("xxx");
    system(a);
   
    pthread_exit(NULL);
    return NULL;
}

int execute(char **argument_list){
    char *path_name = malloc(sizeof(char) * 1024);      //current directory path is saved here
    size_t size = 1024;
    char *read_file = malloc(sizeof(char) * 1024);
    ssize_t r;
    int fd;

    if(argument_list[0]==NULL){
        return 1;
    }
 
    else if(strcmp(argument_list[0], "cd") == 0){
        cd_func(argument_list);
    }
    else if(strcmp(argument_list[0], "echo") == 0){
        echo_command(argument_list);
    }
    else if(strcmp(argument_list[0], "pwd") == 0){
        if(argument_list[1] == NULL){
            printf("%s", getcwd(path_name, size));
            printf("\n");
        }
        else if(strcmp(argument_list[1], "-L") == 0){
            printf("%s", getcwd(path_name, size));
            printf("\n");
        }
        else if(strcmp(argument_list[1], "-P") == 0){
            printf("%s", getcwd(path_name, size));
            printf("\n");
        }
        else{
            printf("Too many arguments");
            printf("\n");
        }
        
    }

    else if(strcmp(argument_list[numOfArgs-1], "&t") == 0){
        pthread_t thready;
        pthread_create(&thready, NULL, &thread_launch, argument_list);
        pthread_join(thready, NULL);
    }

    
    else{
        if(strcmp(argument_list[0], "ls") == 0){
        start(argument_list, "/Users/anubhav/Documents/OS/ls_command");
    }
    else if(strcmp(argument_list[0], "cat") == 0){
        start(argument_list, "/Users/anubhav/Documents/OS/cat_command");
    }
    else if(strcmp(argument_list[0], "date") == 0){
        start(argument_list, "/Users/anubhav/Documents/OS/date_command");
    }
    else if(strcmp(argument_list[0], "mkdir") == 0){
        start(argument_list, "/Users/anubhav/Documents/OS/mkdir_command");
    }
    else if(strcmp(argument_list[0], "rm") == 0){
        start(argument_list, "/Users/anubhav/Documents/OS/rm_command");
    }
    else{
        return 1;
    }
    }
    
    return 1;
}

int start(char **argument_list, char *path){
    pid_t pid;
    pid_t wait_pid;
    int status;

    argument_list[numOfArgs  ] = "none";             //none indicates no argument
    argument_list[numOfArgs+1] = "none";
    argument_list[numOfArgs+2] = "none";
    argument_list[numOfArgs+3] = "none";
    argument_list[numOfArgs+4] = "none";
    argument_list[numOfArgs+5] = "none";

    pid = fork();
    if(pid == 0){
        if(execl(path, argument_list[0], argument_list[1], argument_list[2], argument_list[3], argument_list[4], NULL) == -1){
            perror("Process not executed");
            exit(EXIT_FAILURE);
        }
    }
    else if(pid < 0){
        perror("Forking error!");
        printf("\n");
    }
    else{
        wait_pid = waitpid(pid, &status, WUNTRACED);
        while(!WIFEXITED(status) && !WIFSIGNALED(status)){
            wait_pid = waitpid(pid, &status, WUNTRACED);
        }
    }
    return 1;
}


void shell_loop(){
    char *line;             //get input from terminal
    char **args;            //stores arguments
    int status = 1;         //status of the shell
    char percent = '%';
    while(status){
        // printf("\n");
        char dir2[300];
        printf("anubhav@MacBook-Air-4 ~ %c", percent);
       
        line = readLine();
        args = getArgs(line);
        status = execute(args);
    }
}

int main(int argc, char **argv){
    shell_loop();
    return EXIT_SUCCESS;
}
