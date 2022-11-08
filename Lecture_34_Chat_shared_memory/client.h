#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "chat.h"

#define SHARED_MEMORY_OBJECT_NAME "SHM"
#define SHARED_MEMORY_OBJECT_SIZE sizeof(message_buf)
#define MAX_MESSAGES_NUMBER (200)
#define MSGSZ (128)

typedef struct msgbuf
{
    int m_msg_id;
    char m_user_name[30];
    char m_text[MSGSZ];
    struct msgbuf *next;
} message_buf;

void init_client(int userid, char *username);

void finalize_client(void);

void send_message(char *message);

void recv_message(char *message);

void *recv_handler(void *arg);

#endif /* _CLIENT_H_ */
