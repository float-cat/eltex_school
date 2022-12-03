#ifndef _CLIENT_C_
#define _CLIENT_C_

#include "client.h"

int msqid_send = 0;
int msqid_recv = 0;

void init_client(int userid, char *username)
{
    int msgflg;
    message_buf sbuf;
    pthread_t thrd;
    key_t key_send;
    key_t key_recv;
    msgflg = 0666;
    key_send = 5 + userid * 10;
    key_recv = 10 + userid * 10;
    if ((msqid_send = msgget(key_send, msgflg )) < 0)
    {
    	perror("msgget");
        exit(1);
    }
    if ((msqid_recv = msgget(key_recv, msgflg )) < 0)
    {
        perror("msgget");
        exit(1);
    }
    sbuf.mtype = 2;
    strcpy(sbuf.mtext, username);
    if (msgsnd(msqid_send, &sbuf, sizeof(sbuf), IPC_NOWAIT) < 0)
    {
        perror("msgsnd");
        exit(1);
    }
    pthread_create(&thrd, 0, recv_handler, NULL);
}

void send_message(char *message)
{
    message_buf sbuf;
    sbuf.mtype = 1;
    strcpy(sbuf.mtext, message);
    if (msgsnd(msqid_send, &sbuf, sizeof(sbuf), IPC_NOWAIT) < 0)
    {
        perror("msgsnd");
        exit(1);
    }
}

void recv_message(char *message)
{
    message_buf sbuf;
    msgrcv(msqid_recv, &sbuf, sizeof(sbuf), 0, 0);
    strcpy(message, sbuf.mtext);
}

void *recv_handler(void *arg)
{
    char message[MAX_CHAT_MESSAGE];
    if(arg != NULL)
        return arg;
    while(1)
    {
        usleep(500000);
        recv_message(message);
        print_message(message);
        
    }
    return NULL;
}

#endif /* _CLIENT_C_ */
