/*************************************************************************
	> File Name: getopt.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月27日 星期一 14时51分00秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    int ch;
    
    ch = getopt(argc, argv, "a:bc::");
    switch(ch) {
        case 'a':printf("choise : %c,%s\n",ch,optarg);break;
        case 'b':printf("choise : %c\n",ch);break;
        case 'c':printf("choise : %c, %s\n",ch,optarg);break;
        default :printf("other choise %c\n",ch);break;
    }
    return 0;
}
