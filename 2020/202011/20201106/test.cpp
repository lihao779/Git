#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


#define EAT  2
#define MAKE 2
pthread_mutex_t tex;
pthread_cond_t Eat_cond;
pthread_cond_t Make_cond;
int G_val = 1;



void* pthread_eat(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&tex);
        while(G_val == 0) //---------判断条件只需要按一个一份代码考虑，因为同一时间只能有一个人执行这段代码
        {
            pthread_cond_wait(&Eat_cond,&tex);
        }
        printf("i am %p,i am eatting %d\n",pthread_self(),G_val);
        G_val--;
        pthread_mutex_unlock(&tex);
        pthread_cond_signal(&Make_cond);
    }
}
void* pthread_make(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&tex);
        while(G_val == 1)
        {
            pthread_cond_wait(&Make_cond,&tex);
        }
        printf("i am %p,i am making %d\n",pthread_self(),G_val);
        G_val++;
        pthread_cond_signal(&Eat_cond);
        pthread_mutex_unlock(&tex);
    }
}



int main()
{
    pthread_cond_init(&Eat_cond,NULL);
    pthread_cond_init(&Make_cond,NULL);
    pthread_mutex_init(&tex,NULL);
    pthread_t tid_eat[EAT];
    pthread_t tid_make[MAKE];

    for(int i = 0;i<EAT;++i)
    {
       int ret =  pthread_create(&tid_eat[i],NULL,pthread_eat,NULL);
       if(ret < 0)
       {
           perror("pthread_create");
           return -1;
       }
    }
    for(int i = 0;i<MAKE;++i)
    {
       int ret =  pthread_create(&tid_make[i],NULL,pthread_make,NULL);
       if(ret < 0)
       {
           perror("pthread_create");
           return -1;
       }
    }
    for(int i = 0;i<EAT;++i)
    {
        pthread_join(tid_eat[i],NULL);
    }
    for(int i = 0 ;i<MAKE;++i)
    {
        pthread_join(tid_make[i],NULL);
    }
    pthread_cond_destroy(&Eat_cond); 
    pthread_cond_destroy(&Make_cond); 
    pthread_mutex_destroy(&tex); 
    
    return 0;
}
