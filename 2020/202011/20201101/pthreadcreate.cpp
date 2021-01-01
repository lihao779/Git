#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define THREAD_COUNT 4

struct ThreadDate
{
    int num_; 
    ThreadDate()
    {
        num_ = -1;
    }
};



class Date
{
    public:
        void SetDate(int date)
        {
            date_ = date;
        }
        int GetDate()const
        {
            return date_;
        }
    private:
        int date_;
};

void* ThreadStrat(void* arg)
{
   // ThreadDate* td = (ThreadDate*)arg;
    Date* d = (Date*)arg;
    printf("d->date:%d\n",d->GetDate());
    //printf("td->num_:%d\n",td->num_);
    
    printf("i am ThreadStrat\n");
    //delete td;
    delete d;
    // pthread_exit(NULL); 
    pthread_cancel(pthread_self());
    while(1)
    {
        sleep(1);
    }
    return NULL;
}

int main()
{
    
    pthread_t tid[THREAD_COUNT];
    int i = 0;
    for(i = 0;i<THREAD_COUNT;i++)
    {
        //struct ThreadDate* td = new ThreadDate;
        //td->num_ = i;
        Date* d = new Date;
        d->SetDate(i);
        int ret = pthread_create(&tid[i],NULL,ThreadStrat,(void*)d);
        if(ret < 0)
        {
            return -1;
        }
        pthread_detach(tid[i]);//分离就不用等待了
    }
    for(i = 0;i<THREAD_COUNT;i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    

    while(1)
        ;
    return 0;
}
