#include <stdio.h>

int main()
{
    int a = 1;
    const int& ra = +a;//只要参与运算都取得是右侧的值
    int& rra = a;
    printf("%p,%p,%p\n",&a,&ra,&rra);
    bool b = true;
    if(-b)
    {
        printf("ture,%d\n",-b);
    }
    printf("%d\n",1%-2);
    return 0;
}
