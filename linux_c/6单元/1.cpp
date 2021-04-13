#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("./a.out <mode num> <filename>");
        exit(0);
    }
    int mode = 0;
    int mode_u = 0;
    int mode_g = 0;
    int mode_o = 0;
    char* file;

    mode = atoi(argv[1]);
    if(mode < 0 || mode > 777)
    {
        printf("mode failed");
        exit(0);
    }
    mode_u = mode / 100;
    mode_g = (mode - (mode_u * 100)) / 10;
    mode_o = mode - ((mode_u * 100) + (mode_g * 10));
    mode = mode_u * 8 * 8 + mode_g * 8 + mode_o;
    file = argv[2];
    if(chmod(file, mode) == -1)
    {
        perror("exchange failed");
        exit(0);
    }
        
    return 0;
}
