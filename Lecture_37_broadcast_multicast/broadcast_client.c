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
    char buffer[10];
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int opt=1;  
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("255.255.255.255");
    sa.sin_port = htons(7777);
    int addr_len = sizeof(struct sockaddr);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    recvfrom(sock, buffer, 7, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buffer);
    return 0;
}
