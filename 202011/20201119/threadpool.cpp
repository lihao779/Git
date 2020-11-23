#include<stdio.h>
#include<pthread.h>
#include<queue>
#include<vector>
#include<unistd.h>


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
void handler(int date)
{
    printf("date : %d\n",date);
}

class ThreadPool
{
    public:
    ThreadPool(int thread_count,int capacity)
         :capacity_(capacity)
        ,thread_count_(thread_count)
        ,vec_(thread_count)
    {
        flag = false;
        pthread_mutex_init(&mutex_,NULL);
        pthread_mutex_init(&flag_mutex_,NULL);
        pthread_cond_init(&cond_,NULL);
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_mutex_destroy(&flag_mutex_);
        pthread_cond_destroy(&cond_);
    }
    int Oninit()
    {
        int ret = CreateThread();
        if(ret < 0)
        {
            return -1;
        }
        return 1;
    }
    void Push(Date* date)
    {
        pthread_mutex_lock(&mutex_);
        if(flag)
        {
            pthread_mutex_unlock(&mutex_);
            return ;
        }
        while(que_.size()==capacity_)
        {
            pthread_mutex_unlock(&mutex_);
            return ;
        }
        que_.push(date);
        pthread_mutex_unlock(&mutex_);
        pthread_cond_signal(&cond_);
        
    }
    void Pop(Date** date)
    {
        *date = que_.front();
        que_.pop();
    }
    void Jointhread()
    {
        for(int i = 0;i<thread_count_;i++)
        {
            pthread_join(vec_[i],NULL);
        }
    }
    void Threadpool_Exit()
    {
        pthread_mutex_lock(&flag_mutex_);
        flag = true;
        pthread_mutex_unlock(&flag_mutex_);
        pthread_cond_broadcast(&cond_);
    }
    private:
    int CreateThread()
    {
        for(int i = 0;i<thread_count_;i++)
        {
            int ret = pthread_create(&vec_[i],NULL,StartThread,(void*)this);
            if(ret<0)
            {
                return -1;
            }
        }
        return 1;
    }
    static void* StartThread(void* arg)
    {
       ThreadPool* tp = (ThreadPool*) arg; 
       while(1)
       {
           Date* d;
           pthread_mutex_lock(&tp->mutex_);
           while(tp->que_.empty())
           {
               if(tp->flag)
               {
                   tp->thread_count_--;
                   pthread_mutex_unlock(&tp->mutex_);
                   pthread_exit(NULL);
               }
                pthread_cond_wait(&tp->cond_,&tp->mutex_);
           }
           tp->Pop(&d);
           pthread_mutex_unlock(&tp->mutex_);
           d->Run();
           delete d;
       }
    }
    private:
        std::queue<Date*> que_;
        pthread_mutex_t mutex_;
        pthread_cond_t cond_;
        int capacity_;
        int thread_count_;
        std::vector<pthread_t> vec_;
        pthread_mutex_t flag_mutex_;
        int flag;
};



int main()
{
    ThreadPool* tp = new ThreadPool(4,1);
    int ret = tp->Oninit();
    if(ret < 0)
    {
        printf("失败\n");
    }
    for(int i = 0;i<200;i++)
    {
        Date* d = new Date(i,handler);
        tp->Push(d);
        usleep(1000);
    }
    
    sleep(4);
    tp->Threadpool_Exit();
    tp->Jointhread();
    delete tp; 
    return 0;
}
