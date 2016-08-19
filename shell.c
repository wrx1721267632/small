/*************************************************************************
	> File Name: shell.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月25日 星期六 14时41分49秒
 ************************************************************************/

#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define NO_ONE  0
#define GO_TO  1
#define COME_HERE 2
#define START_END 3

int input_it(char *all)
{
    char ch;
    int i = 0;

    ch = getchar();
    while(i < 256 && ch != '\n') {
        all[i++] = ch;
        ch = getchar();
    }
    //all[i] = '\n';
    //i++;
    all[i] = '\0';

    if(i == 256) {
        printf("command too long\n");
        return 0;
    }
    return 1;
}

void resolve_it(char *all, char com[100][256], int *count)
{
    	char *p = all;
	char *q = all;
	int number = 0;
	while (1) {
		if (p[0] == '\0')
			break;
		if (p[0] == ' ')
			p++;
		else {
			q = p;
			number = 0;
			while((q[0] != ' ') && (q[0] != '\0')) {
				number ++;
				q++;
			}
			strncpy(com[*count], p, number + 1);
			com[*count][number] = '\0';
			*count = *count + 1;
			p = q;
		}
	}
}

int find_command (char **arg) 
{
    DIR *dir;
    char* path[] = {"./", "/bin", "/usr/bin", NULL};
    struct dirent *ptr;
    int i=0;

    if(!strncmp (arg[0], "./", 2)) {
        arg[0] = arg[0] + 2;
    }
    while(path[i] != NULL) {
        if ( (dir = opendir(path[i])) == NULL ){
            printf("can not find_command !\n");
            return 0;
        }
        while((ptr =readdir(dir)) != NULL) {
            if(strcmp(ptr->d_name, arg[0])) {
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
        i++;
    }
    return 0;
}

void do_it(int count, char com[100][256])
{
    int i ;
    char *arg[count];
    int background = 0;
    int flag = 0;
    int how = NO_ONE;
    pid_t pid;
    char file[256];
    int fd;
    int status;

    for (i = 0; i < count; i++) {
        arg[i] = com[i];
    }

    arg[count] = NULL;
 
    if( arg[count - 1][1] == '&' ) {
        background = 1;
    }

    for (i = 0; i < count; i++) {
        if(strcmp (arg[i], ">") == 0) {
            flag ++;
            how = GO_TO;
            if(arg[count + 1] == NULL) {
                flag++;
            }
        }
        if(strcmp(arg[i], "<") == 0) {
            flag ++;
            how = COME_HERE;
            if(arg[count + 1] == NULL) {
                flag++;
            }
        }
        if(strcmp(arg[i], "|") == 0) {
            flag++;
            how = START_END;
            if(arg[count + 1] ==NULL) {
                flag ++;
            }
        }
    }

    if(flag > 1) {
        printf("wrong command!\n");
        return ;
    }

    if((pid = fork()) < 0){
        printf("error\n");
        return ;
    }
    switch(how) {
        case 0:
             if(pid == 0) {
                 if(!find_command(arg) ) {
                    printf("can't find_command !\n");
                   return ;
                }
                execvp(arg[0], arg);
                exit(0);
            }
        break;
        case 1:
            for(i = 0; arg[i] != NULL; i++) {
                if(!strcmp(arg[i], ">")) {
                    strcpy(file, arg[i+1]) ;
                    arg[i] =NULL;
                }
            }
            if(pid == 0) {
                if(!find_command(arg)) {
                    printf("can,t find_command!\n");
                    return ;
                }
                fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
                dup2(fd,1);
                execvp(arg[0], arg);
                exit(0);
            }
        break;
        case 2:
            for(i = 0; arg[i] != NULL; i++) {
                if(!strcmp(arg[i], "<")) {
                    strcpy(file, arg[i+1]) ;
                    arg[i] =NULL;
                }
            }
            if(pid == 0) {
                if(!find_command(arg)) {
                    printf("can,t find_command!\n");
                    return ;
                }
                fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
                dup2(fd,0);
                execvp(arg[0], arg);
                exit(0);
            }
        break;
        default :
            break;
    }
    if (background == 1) {
        printf("[process id : %d]\n", pid);
    }

    if(waitpid(pid, &status, 0) == -1) {
        printf("wait for child process\n");
    }
}

int main()
{
    char *all;
    int i;
    int count = 0;
    char com[100][256];

    all = (char *) malloc (sizeof(char) * 256);
    while(1){
        memset(all, 0, 256);
        printf("linux$$: ");
        if( input_it(all) ){
            if( !strcmp(all,"exit") ) {
                exit(0);
            }
            for( i=0; i<100; i++ ) {
                com[i][0] = '\0';
            }
            count = 0;
            resolve_it(all, com, &count);
            do_it(count, com);
        }
    }
    if(all != NULL){
        free(all);
        all = NULL;
    }

    exit(0);
}
