#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netinet/ip.h>

int main(void)
{
    struct sockaddr_in sa;
    int opt = 1;
    const int *val = &opt;
    char buffer[255];
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    short port = htons(8888);
    short len = htons(235);
    short checksum = 0;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("192.168.1.7");
    sa.sin_port = htons(7777);
    setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(opt));    
    memset(buffer, 0, sizeof(buffer));
    unsigned int addr_len = sizeof(struct sockaddr);
    /* IP header */
	struct iphdr *iph = (struct iphdr *) buffer;
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->frag_off = 0;
	iph->ttl = 64;
	iph->protocol = IPPROTO_UDP;
	iph->daddr = sa.sin_addr.s_addr;

    /* UDP header */
    memcpy(buffer+20, &port, sizeof(short));
    memcpy(buffer+22, &sa.sin_port, sizeof(short));
    memcpy(buffer+24, &len, sizeof(short));
    memcpy(buffer+26, &checksum, sizeof(short));

    /* Data block */
    strcpy(buffer+28, "Hello, world!");
    if(sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr)) < 0)
        perror("sendto failed");
    recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buffer+28);
    return 0;
}
