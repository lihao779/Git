#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define THREAD_COUNT  4
int g_tickests = 100;

struct ThreadDate
{
    int num_; 
    ThreadDate()
    {
        num_ = -1;
    }
};




void* ThreadStrat(void* arg)
{
    ThreadDate* td = (ThreadDate*)arg;

    printf("td->date:%d\n",td->num_);
    
    while(1)
    {
        if(g_tickests>0)
        {
            printf("i am %p-%d,i have ticket is %d\n",pthread_self(),td->num_,g_tickests);
            g_tickests--;
        }
        else
        {
            break;
        }
    }
    delete td;
    return NULL;
}

int main()
{
    
    pthread_t tid[THREAD_COUNT];
    int i = 0;
    for(i = 0;i<THREAD_COUNT;i++)
    {
        struct ThreadDate* td = new ThreadDate;
        td->num_ = i;
        int ret = pthread_create(&tid[i],NULL,ThreadStrat,(void*)td);
        if(ret < 0)
        {
            return -1;
        }
    }
    for(i = 0;i<THREAD_COUNT;i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    

    return 0;
}
