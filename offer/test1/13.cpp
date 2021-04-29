#include <string.h>
#include <string>
#include <iostream>

using namespace std;

bool Increment(char* num)
{
    int result = false;
    int length = strlen(num);

    for(int i = length - 1; i >= 0; i--)
    {
        int temp = num[i] - '0';
        if(temp + 1 < 10)
        {
            num[i] += 1;
            break;
        }
        else
        {
            if(i == 0)
                result = true;
            num[i] = '0';
        }
    }
    return result;
}


void print(char* ptr)
{
    int num = strlen(ptr);
    bool flag = false;
    for(int i = 0 ;i < num; i++)
    {
        if(ptr[i] != '0' && flag == false)
        {
            flag = true;
        }
        printf("%c", ptr[i]);
    }
    printf(" ");
}

void Print(int n)
{
    char* arr = new char[n + 1];
    memset(arr, '0' ,n);
    arr[n] = '\0'; 

    while(!Increment(arr))
        print(arr);
    printf("\n");
    delete[] arr;

}




int main()
{
    int i;
    cin >> i;
    Print(i);
    return 0;
}
