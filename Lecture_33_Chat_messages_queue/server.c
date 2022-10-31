#ifndef _SERVER_C_
#define _SERVER_C_

#include "server.h"

int msqids_send[CLIENT_MAX_COUNT];
int msqids_recv[CLIENT_MAX_COUNT];
args_buf args[CLIENT_MAX_COUNT];

void init_server(void)
{
    int i;
    int msgflg;
    pthread_t pthrs[CLIENT_MAX_COUNT];
    key_t keys_send[CLIENT_MAX_COUNT];
    key_t keys_recv[CLIENT_MAX_COUNT];
    msgflg = IPC_CREAT | 0666;
    for(i = 0; i < CLIENT_MAX_COUNT; i++)
    {
        keys_send[i] = 10 + i * 10;
        keys_recv[i] = 5 + i * 10;
        if ((msqids_send[i] = msgget(keys_send[i], msgflg )) < 0)
        {
            perror("msgget");
            exit(1);
        }
        if ((msqids_recv[i] = msgget(keys_recv[i], msgflg )) < 0)
        {
            perror("msgget");
            exit(1);
        }
        args[i].number = i;
        args[i].name[0] = 0;
        pthread_create(&(pthrs[i]), 0, recv_handler, (void *)&(args[i]));
    }
}

void send_message_to_all(char *user, char *message)
{
    int i;
    message_buf sbuf;
    size_t buf_length;
    sbuf.mtype = 1;
    buf_length = strlen(user);
    strcpy(sbuf.mtext, user);
    strcpy(sbuf.mtext+buf_length, ": ");
    strcpy(sbuf.mtext+(buf_length+2), message);
    for(i = 0; i < CLIENT_MAX_COUNT; i++)
    {
        if (msgsnd(msqids_send[i], &sbuf, sizeof(sbuf), IPC_NOWAIT) < 0)
        {
            perror("msgsnd");
            exit(1);
        }
    }
}

void *recv_handler(void *arg)
{
    args_buf *my_args = (args_buf *)arg;
    args_buf tmp = *my_args;
    message_buf sbuf;
    while(1)
    {
        msgrcv(msqids_recv[tmp.number], &sbuf, sizeof(sbuf), 0, 0);
        if(sbuf.mtype == 2)
            strcpy(tmp.name, sbuf.mtext);
        else
            send_message_to_all(tmp.name, sbuf.mtext);
    }
}

int main(void)
{
    init_server();
    while(1)
    {
        usleep(1000);
    }
    return 0;
}

#endif /* _SERVER_C_ */
