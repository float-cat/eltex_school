#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct ip_header
{
    unsigned version : 4;
    unsigned header_size : 4;
    unsigned dscp : 6;
    unsigned ecn : 2;
    unsigned short packet_size;
    unsigned short id;
    unsigned flags : 3;
    unsigned offset : 13;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    unsigned int source_addr;
    unsigned int dest_addr;
};

int main(void)
{
    struct sockaddr_in sa;
    struct ip_header iph;
    int opt = 1;
    char buffer[255];
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    short port = htons(8888);
    short len = htons(255);
    short checksum = 0;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("0.0.0.0");
    sa.sin_port = htons(7777);
    setsockopt(sock, SOL_SOCKET, IP_HDRINCL, &opt, sizeof(opt));
    int addr_len = sizeof(struct sockaddr);
    memset((char *)&iph, 0, sizeof(iph));
    iph.version = 4;
    iph.header_size = 5;
    iph.packet_size = htons(255);
    iph.flags = 2;
    iph.ttl = 255;
    iph.protocol = 17;
    iph.dest_addr = sa.sin_addr.s_addr;
    memcpy(buffer, &iph, sizeof(iph));
    memcpy(buffer+20, &port, sizeof(short));
    memcpy(buffer+22, &sa.sin_port, sizeof(short));
    memcpy(buffer+24, &len, sizeof(short));
    memcpy(buffer+26, &checksum, sizeof(short));
    strcpy(buffer+28, "Hello, world!");
    sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buffer+28);
    return 0;
}
