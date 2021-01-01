#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void* Test(void* arg)
{
    int res = *(int*)arg;
    cout << res <<endl;
    cout << "hahah" <<endl;
    return NULL;
}

int main()
{
    pthread_t tid;
    int num = 10;
    int res =  pthread_create(&tid,NULL,Test,(void*)&num);
    if(res < 0)
    {
        perror("pthread_create");
        return -1;

    }
    else{
        printf("I am thread\n");

    }
    sleep(1);

}
