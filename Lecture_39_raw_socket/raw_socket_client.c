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
    char buffer[255];
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    short port = htons(8888);
    short len = htons(255);
    short checksum = 0;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("0.0.0.0");
    sa.sin_port = htons(7777);
    int addr_len = sizeof(struct sockaddr);
    memcpy(buffer, &port, sizeof(short));
    memcpy(buffer+2, &sa.sin_port, sizeof(short));
    memcpy(buffer+4, &len, sizeof(short));
    memcpy(buffer+6, &checksum, sizeof(short));
    strcpy(buffer+8, "Hello, world!");
    sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buffer+28);
    return 0;
}
