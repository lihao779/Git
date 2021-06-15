#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>

using namespace std;

#define MAXQUE 5
class Ringque
{
    private:
        int capacity_;
        vector<int> vec;
        int read_;
        int write_;
        sem_t sem_full_;
        sem_t sem_empty_;
        sem_t lock_;
    public:
        Ringque(int que = MAXQUE):capacity_(que), vec(que), read_(0), write_(0)
        {
            sem_init(&sem_empty_, 0, que);
            sem_init(&sem_full_, 0, 0);
            sem_init(&lock_, 0, 1);
        }
        ~Ringque()
        {
            sem_destroy(&sem_full_);
            sem_destroy(&sem_empty_);
            sem_destroy(&lock_);
        }

        bool push(const int& data)
        {
            sem_wait(&sem_empty_);
            sem_wait(&lock_);
            vec[write_] = data;
            write_ = (write_ + 1)%capacity_;
            sem_post(&lock_);
            sem_post(&sem_full_);
            return true;
        }
        bool pop(int* data)
        {
            sem_wait(&sem_full_);
            sem_wait(&lock_);
            *data = vec[read_];
            read_ = (read_ + 1)%capacity_;
            sem_post(&lock_);
            sem_post(&sem_empty_);
            return true;
        }
};

void* Production(void* arg)
{
    Ringque* q = (Ringque*) arg;

    int data = 1;
    while(1)
    {
        q->push(data++);
        printf("push data is %d\n", data);
    }
    return NULL;
}

void* Constomer(void* arg)
{
    Ringque* q = (Ringque*) arg;
    while(1)
    {
        int data = 0;
        q->pop(&data);
        printf("pop data is %d\n", data);
    }
    return NULL;
}
int main()
{
    Ringque q;
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
