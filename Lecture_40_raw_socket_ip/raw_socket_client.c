#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

unsigned short csum(unsigned short *buf, int nwords)
{
  unsigned long sum;
  for(sum=0; nwords>0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum &0xffff);
  sum += (sum >> 16);
  return (unsigned short)(~sum);
}

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
    short len = htons(235);
    short checksum = 0;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(7777);
    setsockopt(sock, SOL_SOCKET, IP_HDRINCL, &opt, sizeof(opt));
    unsigned int addr_len = sizeof(struct sockaddr);
    memset(&iph, 0, sizeof(iph));
    iph.version = 4;
    iph.header_size = 5;
    iph.dscp = 0;
    iph.id = htons(12345);
    iph.packet_size = htons(255);
    iph.flags = 0;
    iph.ttl = 64;
    iph.protocol = IPPROTO_UDP;
    iph.source_addr = sa.sin_addr.s_addr;
    iph.dest_addr = sa.sin_addr.s_addr;
    memcpy(buffer, &iph, sizeof(iph));
    memcpy(buffer+20, &port, sizeof(short));
    memcpy(buffer+22, &sa.sin_port, sizeof(short));
    memcpy(buffer+24, &len, sizeof(short));
    memcpy(buffer+26, &checksum, sizeof(short));
    strcpy(buffer+28, "Hello, world!");
    iph.checksum = csum((unsigned short *)buffer, sizeof(buffer));
    memcpy(buffer, &iph, sizeof(iph));
    sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
    /**/
    memcpy(&iph, buffer, sizeof(iph));
    printf("version = %d\n", iph.version);
    printf("header_size = %d\n", iph.header_size);
    printf("dscp = %d\n", iph.dscp);
    printf("ecn = %d\n", iph.ecn);
    printf("packet_size = %X\n", iph.packet_size);
    printf("id = %d\n", iph.id);
    printf("flags = %d\n", iph.flags);
    printf("offset = %d\n", iph.offset);
    printf("ttl = %d\n", iph.ttl);
    printf("protocol = %d\n", iph.protocol);
    printf("checksum = %d\n", iph.checksum);
    printf("source_addr = %d\n", iph.source_addr);
    printf("dest_addr = %d\n", iph.dest_addr);
    /**/
    printf(buffer+28);
    return 0;
}
