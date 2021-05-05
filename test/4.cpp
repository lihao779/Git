#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int ticks = 100;

pthread_mutex_t mutex;

void* startfunc(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(ticks > 0)
        {
            usleep(1);
            printf("%ld抢到了第%d张票\n", pthread_self(), ticks--);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid[4];
    for(int i = 0;i < 4; i++)
    {
        pthread_create(&tid[i], NULL, startfunc, NULL);
    }

    for(int i = 0; i < 4; i++)
        pthread_join(tid[i], NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
