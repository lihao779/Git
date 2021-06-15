#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>

using namespace std;
typedef void(*handler_t)(int);
class Threadtask
{
    private:
        int data_;
        handler_t handler_; 
    public:
        Threadtask(){}
        Threadtask(int data, handler_t handler) : data_(data), handler_(handler)
        {}
        void Run()
        {
            handler_(data_);
        }
};

#define MAXQUE 1024
#define TID_COUNT 4
class Queue
{
    public:
        Queue(int quecapacity = MAXQUE) : capacity_(quecapacity)
        {
            pthread_mutex_init(&mut_, NULL);
            pthread_cond_init(&ccond_, NULL);
            pthread_cond_init(&pcond_, NULL);
            pthread_create(NULL, NULL, checkiscallallccond, this);
        }

        ~Queue()
        {
            pthread_mutex_destroy(&mut_);
            pthread_cond_destroy(&ccond_);
            pthread_cond_destroy(&pcond_);
        }

        bool Push(Threadtask data)
        {
            pthread_mutex_lock(&mut_);
            while(que_.size() == capacity_)
                pthread_cond_wait(&pcond_, &mut_);
            que_.push(data);
            pthread_cond_signal(&ccond_);
            pthread_mutex_unlock(&mut_);
            return true;
        }
        bool Pop(Threadtask* data)
        {
            pthread_mutex_lock(&mut_);
            while(que_.empty())
            {
                pthread_cond_wait(&ccond_, &mut_);
                if(iscallallccond)
                {
                    pthread_mutex_unlock(&mut_);
                    return true;
                }
            }
            *data = que_.front();
            que_.pop();
            pthread_cond_signal(&pcond_);
            pthread_mutex_unlock(&mut_);
            return true;
        }
        void Iscallallccond()
        {
            iscallallccond = true;
        }
    private:
        static void* checkiscallallccond(void* arg)
        {
            pthread_detach(pthread_self());
            Queue* q = (Queue*)arg;
            while(1)
            {
                sleep(5);
                if(q->iscallallccond)
                    pthread_cond_broadcast(&q->ccond_);
                break;
            }
            return NULL;
        }
    private:
        std::queue<Threadtask> que_;
        pthread_mutex_t mut_;
        pthread_cond_t pcond_;
        pthread_cond_t ccond_;
        int capacity_;
        bool iscallallccond = false;
};



class ThreadPool
{
    private:
        Queue que_;
        vector<pthread_t> vec_tid_; 
        int tid_count_;
        bool isdestory_;
    public:
        ThreadPool(int tid_count = TID_COUNT) : vec_tid_(tid_count), tid_count_(tid_count), isdestory_(false)
        {
            for(int i = 0; i < tid_count_; i++)
            {
               pthread_create(&vec_tid_[i], NULL, work, this); 
            }
        }
        ~ThreadPool()
        {}

        void Push(Threadtask& task)
        {
            que_.Push(task);
        }
        void Destory()
        {
            //..
            isdestory_ = true;
            que_.Iscallallccond();
        }
    private:
        static void* work(void* arg)
        {
            ThreadPool* pool = (ThreadPool*)arg;
            while(1)
            {
                Threadtask task;
                pool->que_.Pop(&task);
                task.Run();
                if(pool->isdestory_)
                    break;
            }
            return NULL;
        }
        
};
