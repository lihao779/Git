#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int desk = 0;
pthread_mutex_t mut;
pthread_cond_t pcond;
pthread_cond_t ccond;


void* Production(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mut);
        while(desk > 0)
        {
            pthread_cond_wait(&pcond, &mut);
        }
        desk++;
        printf("%p product %d\n", pthread_self(), desk);
        pthread_cond_signal(&ccond);
        pthread_mutex_unlock(&mut);
    }
    return NULL;
}
void* Constomer(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mut);
        while(desk <= 0)
        {
            pthread_cond_wait(&ccond, &mut);
        }
        desk--;
        printf("%p constomer %d\n", pthread_self(), desk);
        pthread_cond_signal(&pcond);
        pthread_mutex_unlock(&mut);
    }
    return NULL;
}



int main()
{
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&ccond, NULL);
    pthread_cond_init(&pcond, NULL);
    pthread_t ptid[2], ctid[2];
    int ret = 0;
    for(int i = 0; i < 2;i++)
    {
        ret = pthread_create(&ptid[i], NULL, Production, NULL);
        if(ret != 0)
        {
            printf("create Production failed");
            return -1;
        }
        ret = pthread_create(&ctid[i], NULL, Constomer, NULL);
        if(ret != 0)
        {
            printf("create Production failed");
            return -1;
        }
    }

    for(int i = 0; i < 2;i++)
    {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }

    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&ccond);
    pthread_cond_destroy(&pcond);

    return 0;
}
