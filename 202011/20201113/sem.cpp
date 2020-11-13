#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<pthread.h>
#include<semaphore.h>
#define CAPACITY 9
#define Thread_Count 10

class Sem
{
    public:
        Sem()
            :v_(CAPACITY)
        {
            capacity_ = CAPACITY;
            sem_init(&read_,0,0);
            sem_init(&write_,0,CAPACITY);
            sem_init(&lock_,0,1);
            pushindex = 0;
            popindex = 0;
        }
        void Push(int date)
        {
            sem_wait(&write_);
            sem_wait(&lock_);
            v_[pushindex] = date;
            pushindex = (pushindex+1)%CAPACITY;
            sem_post(&lock_);
            sem_post(&read_);
        }
        void Pop(int* date)
        {
            sem_wait(&read_);
            sem_wait(&lock_);
            *date = v_[popindex];
            popindex = (popindex+1)%CAPACITY;
            sem_post(&lock_);
            sem_post(&write_);

        }
        ~Sem()
        {
            sem_destroy(&read_);
            sem_destroy(&write_);
            sem_destroy(&lock_);
        }
    private:
        std::vector<int> v_;
        int capacity_;
        sem_t read_;
        sem_t write_;
        sem_t lock_;
        int pushindex;
        int popindex;
};

sem_t lock;
void* ReadStart(void* arg)
{
    Sem* Queue =(Sem*)arg;
    int date = 0;
    while(1)
    {
        Queue->Pop(&date);
        printf("i am %p read,i am readnum %d\n",pthread_self(),date);
    }
    return NULL;
}
int count = 0;
void* WriteStart(void* arg)
{
    Sem* Queue = (Sem*)arg;
    while(1)
    {
        sem_wait(&lock);
        Queue->Push(count);
        printf("i am %p write,i am write num is %d\n",pthread_self(),count);
        count++;
        sem_post(&lock);
    }
    return NULL;
}

int main()
{
    sem_init(&lock,0,1);
    Sem* Queue = new Sem;
    pthread_t tid_read[Thread_Count],tid_write[Thread_Count];
    for(int i = 0;i<Thread_Count;i++)
    {
        int ret = pthread_create(&tid_read[i],NULL,ReadStart,(void*)Queue);
        if(ret < 0)
        {
            perror("Read pthread_create");
            return -1;
        }
        ret = pthread_create(&tid_write[i],NULL,WriteStart,(void*)Queue);
        if(ret < 0)
        {
            perror("Write pthread_create");
            return -1;
        }
    }
    for(int i = 0;i<Thread_Count;i++)
    {
        pthread_join(tid_read[i],NULL);
        pthread_join(tid_write[i],NULL);
    }
    delete Queue;
    sem_destroy(&lock);
    return 0;
}
