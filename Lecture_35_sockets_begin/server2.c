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
    struct sockaddr_un sa;
    char buffer[255];
    int sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
    int opt = 1;
    memset(&sa, 0, sizeof(sa));
    sa.sun_family = AF_LOCAL;
    strcpy(sa.sun_path, "/tmp/connect");
    int addr_len = SUN_LEN(&sa);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(sock, (struct sockaddr *)&sa, SUN_LEN(&sa));
    while(1)
    {
        recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
        printf(buffer);
        fflush(stdout);
        sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, SUN_LEN(&sa));
    }
    close(sock);
    return 0;
}
