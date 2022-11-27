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
    struct sockaddr_in sa;
    char buf[25];
    int fdnew, sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_port = htons(7777);
    int addr_len = sizeof(struct sockaddr);
    connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    strcpy(buf, "Hi!");
    send(sock, buf, 4, 0);
    recv(sock, buf, 7, MSG_WAITALL);
    printf("%s\n", buf);
    close(sock);
    return 0;
}
