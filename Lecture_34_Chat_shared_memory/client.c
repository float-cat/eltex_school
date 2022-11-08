#ifndef _CLIENT_C_
#define _CLIENT_C_

#include "client.h"

int shm = 0;
int last_id = -1;
message_buf *addr;
int usr_id = 0;
char usr_name[30];

void init_client(int userid, char *username)
{
    int msgflg = O_CREAT;
    pthread_t thrd;
    if ( (shm = shm_open(SHARED_MEMORY_OBJECT_NAME, msgflg|O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return;
    }
    if ( ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE*MAX_MESSAGES_NUMBER) == -1 ) {
        perror("ftruncate");
        return;
    }
    usr_id = userid;
    strcpy(usr_name, username);
    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (message_buf *)-1 ) {
        perror("mmap");
        return;
    }
    addr->m_user_name[0] = 0;
    pthread_create(&thrd, 0, recv_handler, NULL);
}

void finalize_client(void)
{
    shm_unlink(SHARED_MEMORY_OBJECT_NAME);
}

void send_message(char *message)
{
    message_buf *sbuf, *tmp;
    if(addr->m_user_name[0] == 0)
    {
        addr->m_msg_id = 0;
        strcpy(addr->m_user_name, usr_name);
        strcpy(addr->m_text, message);
        addr->next = NULL;
    }
    else
    {
        tmp = addr;
        while(tmp->next != NULL)
            tmp = tmp->next;
        sbuf = tmp->next = mmap(tmp, SHARED_MEMORY_OBJECT_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
        sbuf->m_msg_id = tmp->m_msg_id + 1;
        strcpy(sbuf->m_user_name, usr_name);
        strcpy(sbuf->m_text, message);
        sbuf->next = NULL;
    }
}

void recv_message(char *message)
{
    size_t buf_length;
    message_buf *sbuf = addr;
    usleep(100000);
    while(sbuf!=NULL)
    {
        if(sbuf->m_msg_id > last_id)
            break;
    }
    if(sbuf != NULL && sbuf->m_user_name[0] != 0)
    {
        last_id = sbuf->m_msg_id;
        buf_length = strlen(sbuf->m_user_name);
        strcpy(message, sbuf->m_user_name);
        strcpy(message + buf_length, ": ");
        strcpy(message + (buf_length+2), sbuf->m_text);
    }
    else
        message[0] = 0;
}

void *recv_handler(void *arg)
{
    char message[MAX_CHAT_MESSAGE];
    if(arg != NULL)
        return arg;
    while(1)
    {
        recv_message(message);
        if(message[0] != 0)
            print_message(message);
    }
    return NULL;
}

#endif /* _CLIENT_C_ */
