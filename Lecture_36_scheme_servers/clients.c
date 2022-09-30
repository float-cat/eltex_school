#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENT 20

void * client_process(void *params)
{
    int bytes;
    char buffer[255] = "Hello, World!";
    struct sockaddr_in sa;
    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family = PF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_port = htons(3000);
    connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    send(sock, buffer, 255, 0);
    bytes = recv(sock, buffer, 255, MSG_WAITALL);
    if(bytes > 0)
    {
        printf(buffer);
        fflush(stdout);
    }
}

int main(void)
{
    int i;
    pthread_t clients[MAX_CLIENT];
    for(i=0; i<MAX_CLIENT; i++)
    {
        pthread_create(&clients[i], NULL, client_process, NULL);
    }
    for(i=0; i<MAX_CLIENT; i++)
    {
        pthread_join(clients[i], NULL);
    }
    return 1;
}
