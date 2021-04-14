#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>


#define IPC_KEY 0x12345678

int main()
{
    
    int shmid = shmget(IPC_KEY, 4096, IPC_CREAT|0664);
    if(shmid < 0)
    {
        perror("shmget error");
        return -1;
    }
    void* ptr ;
    ptr = shmat(shmid, NULL, 0);
    if(ptr == (void*)-1)
    {
        perror("shmat error");
        return -1;
    }

    while(1)
    {
        printf("%s\n", (char*)ptr);
        sleep(1);
    }

    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
