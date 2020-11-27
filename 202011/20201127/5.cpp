#include <stdio.h>
#include <string.h>
int main()
{
    char p1[15] = "abcd",*p2 = "ABCD",str[50] = "xyz";
    char* ptr = strcat(p1+2,p2+1);
    printf("%s\n",ptr);
    printf("%s\n",p1);
    
    return 0;
}
