#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    struct sockaddr_in sa, client;
    char buf[25];
    int fdnew, sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(7777);
    int addr_len = sizeof(struct sockaddr);
    bind(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    listen(sock, 5);
    while(1)
    {
        fdnew = accept(sock, 0, 0);
        recv(fdnew, buf, 4, MSG_WAITALL);
        printf("%s\n", buf);
        strcpy(buf, "Hello!");
        send(fdnew, buf, 7, 0);
        close(fdnew);
    }
    close(sock);
    return 0;
}
