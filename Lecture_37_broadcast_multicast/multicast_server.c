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
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int opt=1;
    struct ip_mreq mreq;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)); 
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("224.0.0.255");
    sa.sin_port = htons(7777);
    inet_aton("224.0.0.255", &(mreq.imr_multiaddr));
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    while(1)
    {
        sendto(sock, "Hello!", 7, 0, (struct sockaddr *)&sa, sizeof(struct sockaddr));
        usleep(1000);
    }
    return 0;
}
