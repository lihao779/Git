#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define THREAD_COUNT  4
int g_tickests = 100;

pthread_mutex_t tex;


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

   /*加锁位置
    * 第一次使用临界资源时
    * 解锁位置
    * 任何有可能退出的地方
    */
    while(1)
    {
        pthread_mutex_lock(&tex);
        if(g_tickests>0)
        {
            g_tickests--;
            printf("i am %p-%d,i have ticket is %d\n",pthread_self(),td->num_,g_tickests);
        }
        else
        {
            pthread_mutex_unlock(&tex);
            break;
        }
        pthread_mutex_unlock(&tex);
    }
    delete td;
    return NULL;
}

int main()
{
    pthread_mutex_init(&tex,NULL);

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
    
    pthread_mutex_destroy(&tex);

    return 0;
}
