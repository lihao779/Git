#include <pthread.h>
#include <queue>
#include <iostream>

#define MAXQUE 1024

class Queue
{
    public:
        Queue(int quecapacity = MAXQUE) : capacity_(quecapacity)
        {
            pthread_mutex_init(&mut_, NULL);
            pthread_cond_init(&ccond_, NULL);
            pthread_cond_init(&pcond_, NULL);
        }

        ~Queue()
        {
            pthread_mutex_destroy(&mut_);
            pthread_cond_destroy(&ccond_);
            pthread_cond_destroy(&pcond_);
        }

        bool Push(int data)
        {
            pthread_mutex_lock(&mut_);
            while(que_.size() == capacity_)
                pthread_cond_wait(&pcond_, &mut_);
            que_.push(data);
            pthread_cond_signal(&ccond_);
            pthread_mutex_unlock(&mut_);
            return true;
        }
        bool Pop(int* data)
        {
            pthread_mutex_lock(&mut_);
            while(que_.empty())
                pthread_cond_wait(&ccond_, &mut_);
            *data = que_.front();
            que_.pop();
            pthread_cond_signal(&pcond_);
            pthread_mutex_unlock(&mut_);
            return true;
        }
    private:
        std::queue<int> que_;
        pthread_mutex_t mut_;
        pthread_cond_t pcond_;
        pthread_cond_t ccond_;
        int capacity_;
};

void* Production(void* arg)
{
    Queue* q = (Queue*) arg;

    int data = 1;
    while(1)
    {
        q->Push(data++);
        printf("push data is %d\n", data);
    }
    return NULL;
}

void* Constomer(void* arg)
{
    Queue* q = (Queue*) arg;
    while(1)
    {
        int data = 0;
        q->Pop(&data);
        printf("pop data is %d\n", data);
    }
    return NULL;
}
int main()
{
    Queue q;
    pthread_t ptid[4], ctid[4];
    int ret;
    for(int i = 0; i < 4;i++)
    {
        ret = pthread_create(&ptid[i], NULL, Production, &q);
        if(ret != 0)
        {
            printf("create Production failed");
            return -1;
        }
        ret = pthread_create(&ctid[i], NULL, Constomer, &q);
        if(ret != 0)
        {
            printf("create Production failed");
            return -1;
        }
    }

    for(int i = 0; i < 4;i++)
    {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }
    return 0;
}
