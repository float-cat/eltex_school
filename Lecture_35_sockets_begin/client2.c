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
    char buf[255];
    struct sockaddr_un sa;
    int fd;
    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    memset(&sa, 0, sizeof(sa));
    sa.sun_family = AF_LOCAL;
    strcpy(sa.sun_path, "/tmp/connect");
    int addr_len = SUN_LEN(&sa);
    strcpy(buf, "Hello, world!");
    sendto(fd, buf, 255, 0, (struct sockaddr *)&sa, SUN_LEN(&sa));
    recvfrom(fd, buf, 255, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buf);
    close(fd);
    return 0;
}
