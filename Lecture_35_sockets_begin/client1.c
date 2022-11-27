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
    struct sockaddr_un client;
    int fd, fdnew;
    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, "/tmp/connect");
    connect(fd, (struct sockaddr *)&client, sizeof(struct sockaddr_un));
    strcpy(buf, "Hi!");
    send(fd, buf, 4, 0);
    recv(fd, buf, 7, MSG_WAITALL);
    printf("%s\n", buf);
    close(fd);
    return 0;
}
