#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct srv_data
{
    pthread_t thrd;
    pthread_mutex_t mtx;
    int sock;
};

void * process(int sock)
{
    int bytes;
    char buffer[255];
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

void * server_node(void *server_data)
{
    struct srv_data mtx;
    while(1)
    {
        mtx = *((struct srv_data *) server_data);
        pthread_mutex_lock(&(mtx.mtx));
        if(mtx.sock < 1)
        {
            usleep(100);
        }
        else
        {
            process(mtx.sock);
            close(mtx.sock);
            mtx.sock = 0;
        }
        pthread_mutex_unlock(&(mtx.mtx));
    }
}

void new_pthreads(struct srv_data *mtx, int start, int n)
{
    int i;
    int shift;
    for(i = 0; i < n; i++)
    {
        shift = start + i;
        (mtx+shift)->sock = 0;
        pthread_mutex_init(&((mtx+shift)->mtx), NULL);
        pthread_create(&((mtx+shift)->thrd), NULL, server_node, (void *)(mtx+shift));
    }
}

int search_node(struct srv_data *mtx, int sock)
{
    int i;  
    for(i=0; i<255; i++)
    {  
        if(mtx[i].sock == 0)
        {
            pthread_mutex_lock(&(mtx[i].mtx));
            mtx[i].sock = sock;
            pthread_mutex_unlock(&(mtx[i].mtx));
            return i;
        }
    }
    return -1;
}

int main(void)
{
    struct srv_data mtx[255];
    struct sockaddr_in sa;
    int sock;
    char buffer[255];
    int i;
    int start = 0;
    int ret;
    int bytes = 0;
    int listener = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    for(i = 0; i < 255; i++)
        mtx[i].sock = -1;
    start = 5;
    sa.sin_family = PF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(3000);
    bind(listener, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    listen(listener, 1);
    while(1)
    {
        sock = accept(listener, 0, 0);
        ret = search_node(mtx, sock);
        if(ret < 0)
        {
            new_pthreads(mtx, start, 5);            
            start += 5;
            search_node(mtx, sock);            
        }
    }
    return 1;
}
