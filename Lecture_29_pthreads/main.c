#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * thr_body(void *args)
{
    int i;
    int *idx = (int *)args;
    for(i=0; i<200000; i++)
        (*idx)++;
    return NULL;
}

int main(void)
{
    int i;
    int idx = 0;
    int idx2 = 0;
    pthread_t thr1, thr2, thr3, thr4, thr5;
    pthread_create(&thr1, NULL, thr_body, (void *)&idx);
    pthread_create(&thr2, NULL, thr_body, (void *)&idx);
    pthread_create(&thr3, NULL, thr_body, (void *)&idx);
    pthread_create(&thr4, NULL, thr_body, (void *)&idx);
    pthread_create(&thr5, NULL, thr_body, (void *)&idx);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);
    pthread_join(thr4, NULL);
    pthread_join(thr5, NULL);
    for(i=0; i<1000000; i++)
        idx2++;
    printf("idx = %d, idx2 = %d\n", idx, idx2);
    exit(EXIT_SUCCESS);
    return 0;
}
