#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "chat.h"

#define MSGSZ (128)

/*extern int msqid_send;
extern int msqid_recv;*/

typedef struct msgbuf
{
    long mtype;
    char mtext[MSGSZ];
} message_buf;

void init_client(int userid, char *username);

void send_message(char *message);

void recv_message(char *message);

void *recv_handler(void *arg);

#endif /* _CLIENT_H_ */
