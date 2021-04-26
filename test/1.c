#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void* func(void* arg)
{
    char* ptr = (char*)arg;
    while(1)
    {
        sleep(1);
        printf("i am thread---%s\n",ptr);
    }
    return ptr;
}

int main()
{
    pthread_t tid;
    int ret;
    char* ptr = "i am ptr";
    ret = pthread_create(&tid, NULL, func, ptr);
    if(ret != 0)
    {
        printf("pthread_create failed\n");
        return 0;
    }

    while(1)
    {
        sleep(1);
        printf("i am main\n");
    }
    return 0;
}
