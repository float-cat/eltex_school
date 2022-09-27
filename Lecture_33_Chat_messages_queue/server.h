#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define CLIENT_MAX_COUNT (5)
#define MSGSZ (128)

typedef struct msgbuf
{
    long mtype;
    char mtext[MSGSZ];
} message_buf;

void init_server(void);

#endif /* _SERVER_H_ */
