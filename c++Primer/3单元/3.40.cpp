#include <stdio.h>
#include <string.h>


int main()
{
    char str1[] = "hello";
    char str2[] = "world";
    char str3[100] = {0};
    strcpy(str3,str1);
    strcat(str3," ");
    strcat(str3,str2);
    printf("str3:%s\n",str3);
    return 0;
}
