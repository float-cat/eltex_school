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
#include <semaphore.h>

#include "chat.h"

#define SEMAPHORE_OBJECT_NAME "SEMAPHORE"
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

#define _DEBUG_ printf("%s (%d)\n", __FILE__, __LINE__); fflush(stdout);

#endif /* _CLIENT_H_ */
