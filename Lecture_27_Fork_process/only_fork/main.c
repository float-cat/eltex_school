#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    fork();
    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}
