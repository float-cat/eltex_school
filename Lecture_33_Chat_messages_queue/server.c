#ifndef _SERVER_C_
#define _SERVER_C_

#include "server.h"

void init_server(void)
{
    int i;
    int msqids_send[CLIENT_MAX_COUNT];
    int msqids_recv[CLIENT_MAX_COUNT];
    int msgflg;
    key_t keys_send[CLIENT_MAX_COUNT];
    key_t keys_recv[CLIENT_MAX_COUNT];
    msgflg = IPC_CREAT | 0666;
    for(i = 0; i < CLIENT_MAX_COUNT; i++)
    {
        keys_send[i] = 10 + i * 10;
        keys_recv[i] = 5 + i * 10;
        if ((msqids_send[i] = msgget(keys_send[i], msgflg )) < 0) {
            perror("msgget");
            exit(1);
        }
        if ((msqids_recv[i] = msgget(keys_recv[i], msgflg )) < 0) {
            perror("msgget");
            exit(1);
        }
}

void send_message_to_all(user_t user, char *message)
{
    int i;
    message_buf sbuf;
    size_t buf_length;
    sbuf.mtype = 1;
    (void) strcpy(sbuf.mtext, message);
    buf_length = strlen(sbuf.mtext) + 1;
    for(i = 0; i > CLIENT_MAX_COUNT; i++)
    {
        if (msgsnd(msqids_send[i], &sbuf, buf_length, IPC_NOWAIT) < 0)
        {
            perror("msgsnd");
            exit(1);
        }
    }
}

void recv_message(int *msgids, user_t user, char message)

#endif /* _SERVER_C_ */
