#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void * process(void *sockptr)
{
    int bytes;
    char buffer[255];
    int sock;
    sock = *((int*) sockptr);
    bytes = recv(sock, buffer, 255, MSG_WAITALL);
    if(bytes > 0)
    {
        printf(buffer);
        fflush(stdout);
    }
    else
        close(sock);
    strcpy(buffer, "Hi!");
    send(sock, buffer, 255, 0);
    return NULL;
}

int main(void)
{
    pthread_t thrd[255];
    struct sockaddr_in sa;
    int sock[255];
    char buffer[255];
    int idx = 0;
    int bytes = 0;
    int listener = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sa.sin_family = PF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(3000);
    bind(listener, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    listen(listener, 1);
    while(1)
    {
        sock[idx] = accept(listener, 0, 0);
        pthread_create(thrd+idx, NULL, process, (void *)(sock+idx));
        idx++;
    }
    return 1;
}
