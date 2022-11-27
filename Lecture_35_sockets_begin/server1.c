#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
    char buf[25];
    struct sockaddr_un serv, client;
    int fd, fdnew;
    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    memset(&serv, 0, sizeof(serv));
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, "/tmp/connect");
    if(bind(fd, (struct sockaddr *)&serv, SUN_LEN(&serv)) < 0)
    {
        printf("Error!");
    }
    listen(fd, 5);
    fdnew = accept(fd, 0, 0);
    recv(fdnew, buf, 4, MSG_WAITALL);
    printf("%s\n", buf);
    strcpy(buf, "Hello!");
    send(fdnew, buf, 7, 0);
    close(fdnew);
    close(fd);
    return 0;
}
