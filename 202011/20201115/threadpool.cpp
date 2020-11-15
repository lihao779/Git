#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>

typedef void(*Handler)(int);

class Date
{
    public:
        Date(int date,Handler handler)
            :date_(date)
             ,handler_(handler)
        {}
        void Run()
        {
            handler_(date_);
        }
        

    private:
        int date_;
        Handler handler_; 
};

class threadpool
{
    public:
        threadpool(size_t capacity,int threadcount)
        {
            flag = false;
            capacity_ = capacity;
            threadcount_=threadcount;
            vec_.resize(threadcount_);
            pthread_mutex_init(&mutex_,NULL);
            pthread_cond_init(&cond_,NULL);
        }
        ~threadpool()
        {
            pthread_mutex_destroy(&mutex_);
            pthread_cond_destroy(&cond_);
        }

        void Oninit()//启动线程池线程
        {
            CreateThread();
        }
        void Push(Date* d)
        {
            pthread_mutex_lock(&mutex_);
            while(que_.size()>=capacity_)
            {
                pthread_mutex_unlock(&mutex_);
                return ;
            }
            que_.push(d);
            pthread_mutex_unlock(&mutex_);
            pthread_cond_signal(&cond_);
            usleep(200);

        }
        void Pop(Date** d)
        {
            *d = que_.front();
            que_.pop();
        }
        void threadjoin()
        {
            for(int i = 0;i<threadcount_;i++)
            {
                pthread_join(vec_[i],NULL);
            }
        }
        static void* con(void* arg)
        {
            threadpool* tp = (threadpool*) arg;
            while(1)
            {
                pthread_mutex_lock(&tp->mutex_);
                while(tp->que_.size()==0)
                {
                    if(tp->flag)
                    {
                        pthread_mutex_unlock(&tp->mutex_);
                        break;
                    }
                    pthread_cond_wait(&tp->cond_,&tp->mutex_);
                }
                Date* d;
                tp->Pop(&d);
                pthread_mutex_unlock(&tp->mutex_);
                d->Run();
                delete d;

            }
            
        }
        void Destory()
        {
            flag = true;
            pthread_cond_broadcast(&cond_);
        }
    private:
        int  CreateThread()
        {
            for(int i = 0;i<threadcount_;i++)
            {
                int ret = pthread_create(&vec_[i],NULL,con,(void*)this);
                if(ret < 0)
                {
                    perror("pthread_create");
                    return -1;
                }
            }
            return 1;
        }

    private:
        std::queue<Date*> que_;
        pthread_mutex_t mutex_;
        pthread_cond_t cond_;
        size_t capacity_;
        int threadcount_;
        std::vector<pthread_t> vec_; 
        int flag;
};


void func(int date)
{
    printf("date:%d\n",date);
}
int main()
{

    threadpool* tp = new threadpool(10,1);
    tp->Oninit();
    
    for(int i = 0;i<200;i++)
    {
        Date* d = new Date(i,func);
        tp->Push(d);
    }
    tp->threadjoin();
    delete tp;
    return 0;
}
