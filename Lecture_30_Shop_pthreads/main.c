#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mtx[5];
int shops[5];

void * thrd_consumer(void *args)
{
    int shop_id;
    int needs = rand()%1000 + 9500;
    while(needs > 0)
    {
        shop_id = rand()%5;
        pthread_mutex_lock(&mtx[shop_id]);
        if(needs >= shops[shop_id])
        {
            needs -= shops[shop_id];
            shops[shop_id] = 0;
            sleep(2);
        }
        else
        {
            shops[shop_id] -= needs;
            needs = 0;
            pthread_exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&mtx[shop_id]);
    }
    return NULL;
}

void * thrd_deliver(void *args)
{
    int shop_id;
    while(1)
    {
        for(shop_id = 0; shop_id < 5; shop_id++)
        {
            pthread_mutex_lock(&mtx[shop_id]);
            shops[shop_id] += 500;
            pthread_mutex_unlock(&mtx[shop_id]);
        }
        sleep(2);
    }
    return NULL;
}

void * thrd_monitor(void *args)
{
    int shop_id;
    while(1)
    { 
        for(shop_id = 0; shop_id < 5; shop_id++)
        {
            pthread_mutex_lock(&mtx[shop_id]);
            printf("%d ", shops[shop_id]);
            pthread_mutex_unlock(&mtx[shop_id]);
        }
        printf("\n");
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    int i;
    pthread_t thrd1, thrd2, thrd3, thrd4, thrd5;
    srand(time(NULL));
    for(i=0; i<5; i++)
        shops[i] = 0;
    pthread_create(&thrd1, NULL, thrd_consumer, NULL);
    pthread_create(&thrd2, NULL, thrd_consumer, NULL);
    pthread_create(&thrd3, NULL, thrd_consumer, NULL);
    pthread_create(&thrd4, NULL, thrd_deliver, NULL);  
    pthread_create(&thrd5, NULL, thrd_monitor, NULL);    
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);
    exit(EXIT_SUCCESS);
    return 0;
}
