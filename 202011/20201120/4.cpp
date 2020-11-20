#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a = 12345678;
    FILE* pf = fopen("test.txt","wb");
    fwrite(&a,4,1,pf);
    fclose(pf);
    
    return 0;
}
