#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END (0)
#define WRITE_END (1)

int main(void)
{
    int fd[2];
    pid_t pid;
    int status;
    char *ptr;
    char cmdline[50];
    char cmd[50];
    char *argv[3];
    argv[0] = malloc(sizeof(char)*50);
    argv[1] = malloc(sizeof(char)*50);
    argv[2] = NULL;
    char cmd2[50];
    char *argv2[3];
    argv2[0] = malloc(sizeof(char)*50);
    argv2[1] = malloc(sizeof(char)*50);
    argv2[2] = NULL;
    do
    {
        fgets(cmdline, 50, stdin);
        cmdline[strlen(cmdline)-1] = 0;
        ptr = strtok(cmdline, " ");
        strcpy(cmd, ptr);
        strcpy(argv[0], ptr);
        ptr = strtok(NULL, " ");
        strcpy(argv[1], ptr);
        ptr = strtok(NULL, " ");
        printf(ptr);
        if(ptr[0] != '|')
            return 1;
        ptr = strtok(NULL, " ");
        strcpy(cmd2, ptr);
        strcpy(argv2[0], ptr);
        ptr = strtok(NULL, " ");
        strcpy(argv2[1], ptr);

        pipe(fd);
        pid = fork();
        if(pid == 0)
        {
            dup2(fd[WRITE_END], STDOUT_FILENO);
            close(fd[READ_END]);
            close(fd[WRITE_END]);
            execvp(cmd, argv);
        }
        else
        { 
            pid=fork();

            if(pid==0)
            {
                dup2(fd[READ_END], STDIN_FILENO);
                close(fd[WRITE_END]);
                close(fd[READ_END]);
                execvp(cmd2, argv2);
                exit(1);
            }
            else
            {
                int status;
                close(fd[READ_END]);
                close(fd[WRITE_END]);
                waitpid(pid, &status, 0);
            }
        }
    }
    while(strcmp(cmdline, "exit")!=0);
    free(argv[0]);
    free(argv[1]);
    exit(EXIT_SUCCESS);
}
