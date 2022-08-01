#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int pid;
    int status;
    char *ptr;
    char cmdline[50];
    char cmd[50];
    char *argv[3];
    argv[0] = malloc(sizeof(char)*50);
    argv[1] = malloc(sizeof(char)*50);
    argv[2] = NULL;
    do
    {
        fgets(cmdline, 50, stdin);
        cmdline[strlen(cmdline)-1] = 0;
        ptr = strtok(cmdline, " ");
        strcpy(cmd, ptr);
        strcpy(argv[0], ptr);
        ptr = strtok(NULL, " ");
        strcpy(argv[1], ptr);
        pid = fork();
        if(pid)
        {
            execvp(cmd, argv);
        }
        else
            wait(&status);
    }
    while(strcmp(cmdline, "exit")!=0);
    free(argv[0]);
    free(argv[1]);
    exit(EXIT_SUCCESS);
}
