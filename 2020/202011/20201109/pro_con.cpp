#include<stdio.h>
#include<unistd.h>
#include<queue>
#include<pthread.h>

#define CAPACITY 10
#define CONSUMER 7
#define PRODUCT 7

pthread_mutex_t tex_con;
pthread_mutex_t tex_pro;
int count = 0;

class SafeQueue
{
public:
    SafeQueue()
    {
        pthread_mutex_init(&tex_,NULL);
        pthread_cond_init(&con_cond_,NULL);
        pthread_cond_init(&pro_cond_,NULL);
        capacity_ = CAPACITY;
    }
    ~SafeQueue()
    {
        pthread_cond_destroy(&con_cond_);
        pthread_cond_destroy(&pro_cond_);
        pthread_mutex_destroy(&tex_);
    }
    void Push(int date)
    {
        pthread_mutex_lock(&tex_);
        while(q_.size()==capacity_)
        {
            pthread_cond_wait(&pro_cond_,&tex_);
        }
        q_.push(date);
        pthread_mutex_unlock(&tex_);
        pthread_cond_signal(&con_cond_);
    }
    void Pop(int* date)
    {
        pthread_mutex_lock(&tex_);
        while(q_.empty())
        {
            pthread_cond_wait(&con_cond_,&tex_);
        }
        *date = q_.front();
        q_.pop();
        pthread_mutex_unlock(&tex_);
        pthread_cond_signal(&pro_cond_);
    }

private:
    std::queue<int> q_;
    size_t  capacity_;
    pthread_mutex_t tex_;
    pthread_cond_t con_cond_;
    pthread_cond_t pro_cond_;

};



void* product(void* arg)
{
    SafeQueue* q = (SafeQueue*)arg;
    while(1)
    {
        pthread_mutex_lock(&tex_pro);
        q->Push(count);
        printf("i am %p,i product %d\n",pthread_self(),count);
        count++;
        pthread_mutex_unlock(&tex_pro);
    }
    return NULL;
}


void* consumer(void* arg)
{
    SafeQueue* q = (SafeQueue*)arg;
    while(1)
    {
        pthread_mutex_lock(&tex_con);
        int date;
        q->Pop(&date);
        printf("\ti am %p,i consumer %d\n",pthread_self(),date);
        pthread_mutex_unlock(&tex_con);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&tex_con,NULL);
    pthread_mutex_init(&tex_pro,NULL);
    SafeQueue* q = new SafeQueue;
    pthread_t tid_con[CONSUMER],tid_pro[PRODUCT];
    for(int i = 0;i<CONSUMER;++i)
    {
        int ret = pthread_create(&tid_con[i],NULL,consumer,q);
        if(ret < 0)
        {
            perror("CONSUMER-pthread_create");
            return -1;
        }
    }
    for(int i = 0;i<PRODUCT;++i)
    {
        int ret = pthread_create(&tid_pro[i],NULL,product,q);
        if(ret < 0)
        {
            perror("PRODUCT-pthread_create");
            return -1;
        }
    }
    for(int i = 0;i<CONSUMER;++i)
    {
        pthread_join(tid_con[i],NULL);
    }
    for(int i = 0;i<PRODUCT;++i)
    {
        pthread_join(tid_pro[i],NULL);
    }
    delete q;
    pthread_mutex_destroy(&tex_con);
    pthread_mutex_destroy(&tex_pro);
    return 0;
}
