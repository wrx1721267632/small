/*************************************************************************
	> File Name: cpu_zijie.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月18日 星期三 21时21分10秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2) 
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1) 
            printf("small-endian\n");
        else 
            printf("unknown\n");
    } else 
        printf("sizeof(short): %d\n", sizeof(short));
    return 0;
}
