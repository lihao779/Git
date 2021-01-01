#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

int g_val = 100;
pthread_mutex_t tex;
pthread_mutex_t tex2;



void* start1(void* arg)
{
   printf("start1\n");
   pthread_mutex_lock(&tex2);
   sleep(1);
   pthread_mutex_lock(&tex);
   while(1)
   {
        if(g_val>0)
        {
            g_val--;
            printf("start1:g_val = %d\n",g_val);
        }
        else
            break;
   }
    //pthread_mutex_unlock(&tex2);
    //pthread_mutex_unlock(&tex);
}
void* start2(void* arg)
{
    printf("start2\n");
    pthread_mutex_lock(&tex);
   sleep(1);
    pthread_mutex_lock(&tex2);
    while(g_val>0)
    {
        g_val--;
        printf("start2:g_val = %d\n",g_val);
    }
    //pthread_mutex_unlock(&tex);
    //pthread_mutex_unlock(&tex2);
}
/*
 * 互斥锁只约定君子，不约定小人
 * 所有访问临界资源的地方都必须加锁
 * 如果不加锁会----如start1
 * 不用管临界资源有没有加锁
 * 直接访问
 */
int main()
{
    pthread_mutex_init(&tex,NULL);
    pthread_mutex_init(&tex2,NULL);
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,start1,NULL);
    pthread_create(&tid[1],NULL,start2,NULL);

    for(int i = 0;i<2;i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&tex);
    pthread_mutex_destroy(&tex2);
    return 0;
}



/*
 *
 *
 * 死锁
 * 线程1，线程2
 * 拥有锁1，锁2
 * 当线程1先请求1号锁，在请求2号锁，最后解2个锁
 * 线程2先请求2号锁，再请求1号锁，最后解2个锁
 *
 *
 * --------------------------------------
 *  可能线程1抢到1号锁，线程二抢到2号锁，导致死锁
 *
 *
 *  解决办法
 *     顺寻加锁---线程1先加1号锁再加2号锁
 *                线程二先加1号锁再加2号锁
 */
