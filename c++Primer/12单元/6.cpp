#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include <iostream>

using namespace std;


void destory(int* sockfd)
{
    close(*sockfd);
    cout << "sockfd is destory" << endl;
}

void f1()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //shared_ptr<int> ptr(&sockfd, destory);
    shared_ptr<int> ptr(&sockfd, [](int* sockfd){close(*sockfd); cout << "sockfd is destory" << endl;});
    //process sockfd
    //结束sockfd自动销毁
}

int main()
{
    f1();
    unique_ptr<int> ptr1(new int(10));
    unique_ptr<int> ptr2(ptr1);
    unique_ptr<int> ptr3;
    ptr3 = ptr1;
    return 0;
}
