#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PTHREADS 5

struct srv_data
{
    pthread_t thrd;
    pthread_mutex_t mtx;
    int sock;
};

struct task_queue_item
{
    int sock;
    struct task_queue_item *prev;
    struct task_queue_item *next;
};

struct task_queue
{
    struct task_queue_item *root;
    struct task_queue_item *tail;
};

struct process_queue_data
{
    struct srv_data *mtx;
    struct task_queue **tq;
};

struct task_queue * input_queue(struct task_queue *tq, int sock)
{
    struct task_queue_item *elem;
    if(tq == NULL)
    {
        tq = malloc(sizeof(struct task_queue));
        elem = malloc(sizeof(struct task_queue_item));
        elem->prev = NULL;
        elem->next = NULL;
        elem->sock = sock;
        tq->root = elem;
        tq->tail = elem;
    }
    else
    {
        elem = malloc(sizeof(struct task_queue_item));
        elem->prev = NULL;
        elem->next = tq->root;
        elem->sock = sock;
        tq->root->prev = elem;
        tq->root = elem;
    }
    return tq;
}

int output_queue(struct task_queue *tq)
{
    int ret;
    struct task_queue_item *p;
    if(tq == NULL)
    {
        ret = -1;
    }
    else
    {
        ret = tq->tail->sock;
        p = tq->tail;
        tq->tail = tq->tail->prev;
        tq->tail->next = NULL;
        free(p);
    }
    return ret;
}

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

void server_init(struct srv_data *mtx)
{
    int i;
    for(i = 0; i < MAX_PTHREADS; i++)
    {
        (mtx + i)->sock = 0;
        pthread_mutex_init(&((mtx + i)->mtx), NULL);
        pthread_create(&((mtx+i)->thrd), NULL, server_node, (void *)(mtx+i));
    }
}

int search_node(struct srv_data *mtx, int sock)
{
    int i;  
    for(i=0; i<MAX_PTHREADS; i++)
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

void * process_queue(void * params)
{
    struct process_queue_data *p;
    int sock;
    int i;
    p = (struct process_queue_data *)params;
    while(1)
    {
        for(i = 0; i < MAX_PTHREADS; i++)
        {
            if((p->mtx+i)->sock == 0)
            {
                sock = output_queue(*(p->tq));
                if(sock > 0)
                    search_node(p->mtx, sock);
            }
        }
        usleep(100);
    }
    return NULL;
}

int main(void)
{
    struct srv_data mtx[MAX_PTHREADS];
    struct sockaddr_in sa;
    struct task_queue * tq = NULL;
    struct process_queue_data param;
    pthread_t thrd_queue;
    int sock;
    char buffer[255];
    int i;
    int ret;
    int bytes = 0;
    int listener = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    server_init(mtx);
    sa.sin_family = PF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(3000);
    bind(listener, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    listen(listener, 1);
    param.mtx = mtx;
    param.tq = &tq;
    pthread_create(&thrd_queue, NULL, process_queue, (void *)&param);
    while(1)
    {
        sock = accept(listener, 0, 0);
        ret = search_node(mtx, sock);
        if(ret < 0)
            tq = input_queue(tq, sock);
    }
    return 1;
}
