#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct mac_header /* 18 байт */
{
    unsigned char dest_mac[6];
    unsigned char source_mac[6];
    unsigned int label;
    unsigned short type;
};

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
    struct sockaddr_ll sa;
    struct mac_header mach;
    struct ip_header iph;
    unsigned char dmac[6] = {0x34, 0x01, 0x3E, 0x11, 0x45, 0xBC};
    unsigned char smac[6] = {0x74, 0xFF, 0x71, 0xF4, 0xB1, 0xE4};
    int opt = 1;
    char buffer[255];
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    short port = htons(8888);
    short dest_port = htons(7777);
    short len = htons(255);
    short checksum = 0;
    sa.sll_family = AF_PACKET;
    sa.sll_protocol = htons(ETH_P_ALL);
    sa.sll_ifindex = htonl(3);
    sa.sll_pkttype = PACKET_OTHERHOST;
    setsockopt(sock, SOL_SOCKET, IP_HDRINCL, &opt, sizeof(opt));
    int addr_len = sizeof(struct sockaddr_ll);
    memset((char *)&mach, 0, 18);
    memcpy(&(mach.dest_mac), dmac, 6);
    memcpy(&(mach.source_mac), smac, 6);
    mach.label = 0;
    mach.type = 0x0800;
    memset((char *)&iph, 0, sizeof(iph));
    iph.version = 4;
    iph.header_size = 5;
    iph.packet_size = htons(255);
    iph.flags = 2;
    iph.ttl = 255;
    iph.protocol = 17;
    iph.dest_addr = inet_addr("192.168.1.5");
    memcpy(buffer, &mach, 18);
    memcpy(buffer+18, &iph, sizeof(iph));
    memcpy(buffer+38, &port, sizeof(short));
    memcpy(buffer+40, &dest_port, sizeof(short));
    memcpy(buffer+42, &len, sizeof(short));
    memcpy(buffer+44, &checksum, sizeof(short));
    strcpy(buffer+46, "Hello, world!");
    sendto(sock, buffer, 255, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    recvfrom(sock, buffer, 255, 0, (struct sockaddr *)&sa, &addr_len);
    printf(buffer+46);
    return 0;
}
