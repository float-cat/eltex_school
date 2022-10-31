#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define CLIENT_MAX_COUNT (5)
#define MSGSZ (128)
#define MAX_NAME (30)

typedef struct argsbuf
{
    int number;
    char name[MAX_NAME];
} args_buf;

typedef struct msgbuf
{
    long int mtype;
    char mtext[MSGSZ];
} message_buf;

void init_server(void);

void send_message_to_all(char *user, char *message);

void *recv_handler(void *arg);

#endif /* _SERVER_H_ */
