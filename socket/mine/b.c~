/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: 2015年08月04日 星期二 19时15分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#include <time.h> 
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_TO 100
//最大发送长度

#define NO printf("\033[?25l");					
//隐藏光标
#define YES printf("\033[?25h");				
//显示光标

#define MOVEUP(x) printf("\033[%dA", (x))    	
//上移动光标

void Password(char *a, char *b);				
//输入密码
void output_data(int conn_fd);					
//获取服务器发来的数据
void get_data(char *input_buf);					
//消息的输入
void input_data(int conn_fd);					
//向服务器发送数据
char my_page(void);								
//登录页面
int my_denglu(int conn_fd);						
//登录使得函数
void my_zhuce(int conn_fd);						
//注册的函数

pthread_mutex_t mutex;
int signal = 0;
char username_all[32];
int type = 0;

int getch(void) 
{ 
        struct termios tm, tm_old; 
        int fd = STDIN_FILENO, c;
         
        if(tcgetattr(fd, &tm) < 0) 
                return -1; 
        tm_old = tm; 
        cfmakeraw(&tm); 
        
        if(tcsetattr(fd, TCSANOW, &tm) < 0) 
                return -1; 
        c = fgetc(stdin); 
        
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0) 
                return -1; 
        return c; 
} 

void Password(char *a, char *b)
{
	NO; 
	char ch;
        int i=0,j;
     
	while(1)
	{
	   ch=getch();
	   
	   if(ch == 127)
	   {
		if(i != 0){
		   fflush(stdin);
		   b[i-1]='\0';
	           i--;
	        }
	   } else if(ch == 13){
		   break;
	   } else if(ch > 32 && ch < 127){
	     if(i<20){
            b[i]=ch;
	        fflush(stdin);
	     	i++;
 	     }
	   }
       printf("\r%s",a);
	   for(j=0; j<i; j++)
		   printf("*");
	   for(j=0; j<20-i; j++)
		   printf(" ");
	}
	printf("\n");
	YES;
}

void output_data(int conn_fd)
{
    char recv_buf[100];
    time_t timep;
    char a[200];
    int fp;
    
    while(1){
        if(recv(conn_fd, recv_buf, MAX_TO, 0) == 0) {
        	printf("服务器退出\n");
        	exit(0);
        	signal = 1;
        }
        
        if(strcmp(recv_buf, "-exit\n") == 0) {
            break;
        }
        
        if(strcmp(recv_buf, "#xiugai\n") == 0) {
            printf("userpassword: ");
            scanf("%s", recv_buf);
            send(conn_fd, recv_buf, MAX_TO,0);
            continue;
        }
        
        if(strcmp(recv_buf, "#exit\n") == 0) {
        	type = 0;
            send(conn_fd, "#exit\n", MAX_TO,0);
            continue;
        }
        
        if(strcmp(recv_buf, "服务器： don,t online or don't have the person!\n") == 0) {
            signal = 2;
            type = 0;
        }               

        if(signal == 1){
            break;
        }
        
        time (&timep); 
        printf("\r %s\n",recv_buf);
        printf("\033[01;34m \r      %s\n\033[0m",ctime(&timep));
        
        pthread_mutex_lock(&mutex);
		fp = open(username_all, O_WRONLY|O_CREAT|O_APPEND, 0777);
		sprintf(a, " %s\n   %s\n",recv_buf,ctime(&timep));
		write(fp, a, strlen(a));
		close(fp);
		pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void get_data(char *input_buf)
{
    int i = 0;
    char c;
    while( i < 30) {
        c = getchar();
        if(c == '\n') {
            break;
        }
        input_buf[i++] = c;
    }
    input_buf[i++] = '\n';
    input_buf[i++] = '\0';
}



void input_data(int conn_fd)
{
    char input_buf[100];
    int ch;
    char buf[32];
    time_t timep;
    int j;
    int fp;
    char a[200];
    
    while(1) {
        get_data(input_buf);
        if(strncmp(input_buf, "#to ", 4) == 0){
        	type = 1;
        	for(j=4; input_buf[j] != '\n'; j++){
	        	buf[j-4] = input_buf[j];
	    	}
	    	buf[j-4] = '\0';
        }
        
        if(strcmp(input_buf, "#all\n") == 0){
        	type = 2;
        }
        
        if(strcmp(input_buf, "#exit\n") == 0){
        	type = 0;
        }
        
        if(type == 1){
        	MOVEUP(1);
        	time (&timep);
        	printf("\033[01;35m \rinput(to %s): %s\n      %s\033[0m", buf,input_buf,ctime(&timep));
        	send(conn_fd, input_buf, MAX_TO,0);
        	
        	pthread_mutex_lock(&mutex);
			fp = open(username_all, O_WRONLY|O_CREAT|O_APPEND, 0777);
			sprintf(a, "input(to %s): %s\n   %s",buf,input_buf,ctime(&timep));
			write(fp, a, strlen(a));
			close(fp);
			pthread_mutex_unlock(&mutex);
			        
			if(strcmp(input_buf, "-exit\n") == 0) {
            	break;
        	}
        
        	usleep(10); 
        	continue;
        }
        
        if(type == 2){
        	MOVEUP(1);
        	time (&timep);
        	printf("\033[01;35m \rinput(to all): %s\n      %s\033[0m",input_buf,ctime(&timep));
        	send(conn_fd, input_buf, MAX_TO,0);
        	
        	pthread_mutex_lock(&mutex);
			fp = open(username_all, O_WRONLY|O_CREAT|O_APPEND, 0777);
			sprintf(a, "input(to all): %s\n   %s",input_buf,ctime(&timep));
			write(fp, a, strlen(a));
			close(fp);
			pthread_mutex_unlock(&mutex);
			
			if(strcmp(input_buf, "-exit\n") == 0) {
            	break;
        	}
  
        	usleep(10); 
        	continue;
        }
        
        MOVEUP(1);
        time (&timep);
        printf("\033[01;35m \rinput: %s\n      %s\033[0m", input_buf,ctime(&timep));
        send(conn_fd, input_buf, MAX_TO,0);
    	usleep(10); 
        
        if(strcmp(input_buf, "-exit\n") == 0) {
            break;
        }
        
        if(signal == 1){
            break;
        }
    }
    signal = 1;
    pthread_exit(0);
}

char my_page(void)
{
	char ch;
	while(1){
		system("clear");
		printf("\t\t1.登录\n");
    	printf("\t\t2.注册\n");
    	printf("\t\t3.管理员\n");
    	printf("\t\t0.退出\n");
    	printf("请输入需要的操作序号: ");
    	scanf("%c",&ch);
    	getchar();
    	
    	if((ch == '1') || (ch == '2') || (ch == '3')|| (ch == '0')){
    		break;
    	}
    	printf("\n请正确输入！\n");
    	printf("输入任意键退出!\n");
    	getch();
    }
    return ch;
}

int my_denglu(int conn_fd)
{
	char recv_buf[1024];
	int ret;
	pthread_t thid1;
    pthread_t thid2;
	
	send(conn_fd, "denglu", MAX_TO, 0);
    printf("username: ");
    get_data(recv_buf);
    strcpy(username_all, recv_buf);
    username_all[strlen(username_all)-1] = '\0';
    strcat(username_all,".txt");
    send(conn_fd, recv_buf, 32, 0);
    printf("userpassword: ");
    Password("userpassword: ",recv_buf);
    send(conn_fd, recv_buf,32, 0);
    recv(conn_fd, recv_buf, 3, 0);
    printf("\ny/n:  %s", recv_buf);
    
    if(strcmp(recv_buf, "n\n") == 0) {
    	printf("输入任意键继续！\n");
    	getch();    		   
    	return 0;
    }

    if((ret = recv(conn_fd,recv_buf, 100, 0)) < 0) {
    	printf("error 5!\n");
    	exit(1);
    }
   	printf("\033[01;32m       %s\033[0m\n",recv_buf);
    pthread_create(&thid1, NULL, (void *) input_data,  (int *)conn_fd); 
    pthread_create(&thid2, NULL, (void *) output_data,  (int *)conn_fd);
    pthread_join(thid1, NULL);
    return thid1;
}

void my_delete(int conn_fd)
{
	char recv_buf[1024];
	
	while(1){
		printf("请输入要删除的用户名！\n");
		get_data(recv_buf);
		if(strcmp(recv_buf, "-exit\n") == 0){
			exit(0);
		}
		recv_buf[strlen(recv_buf)-1] = '\0';
		send(conn_fd, recv_buf,32,0);
		recv(conn_fd, recv_buf, 32, 0);
		printf("%s\n", recv_buf);
	}
}

void my_guanli(int conn_fd)
{
	char recv_buf[1024];
	char ch;
	
	send(conn_fd, "guanli", MAX_TO, 0);
    printf("username: ");
    get_data(recv_buf);
    send(conn_fd, recv_buf, 32, 0);
    printf("userpassword: ");
    Password("userpassword: ",recv_buf);
    send(conn_fd, recv_buf,32, 0);
    recv(conn_fd, recv_buf, 3, 0);
    printf("\ny/n:  %s", recv_buf);
    
    if(strcmp(recv_buf, "n\n") == 0) {
    	printf("输入任意键继续！\n");
    	getch();    		   
    	exit(0);
    }

    if((ret = recv(conn_fd,recv_buf, 100, 0)) < 0) {
    	printf("error 5!\n");
    	exit(1);
    }
   	printf("\033[01;32m       %s\033[0m\n",recv_buf);
   	while(1){
   		printf("\t\t1.删除\n");
   		printf("\t\t2.记录\n");
   		printf("\t\t0.退出\n");
   		printf("请输入需要的操作序号: ");
    	scanf("%c",&ch);
    	getchar();
    	
    	if((ch == '1') || (ch == '2') || (ch == '0')){
    		break;
    	}
    	printf("\n请正确输入！\n");
    	printf("输入任意键退出!\n");
    	getch();
    }
    switch(ch){
    	    case '1':
    	    	my_delete(conn_fd);
    			break;
    	    case '2':
    			break;
    	    case '0':
    	    	close(conn_fd);
    			exit(0);
    	    default:
    	    	printf("\nplease input a right number!\n");
    	    	break;
    }
}

void my_zhuce(int conn_fd)
{
	char recv_buf[1024];
	
	send(conn_fd, "zhuce", MAX_TO, 0);
    printf("username: ");
    get_data(recv_buf);
    send(conn_fd, recv_buf, 32, 0);
    printf("userpassword: ");
    Password("userpassword: ",recv_buf);
    send(conn_fd, recv_buf,32, 0);
    recv(conn_fd, recv_buf, MAX_TO, 0);
    printf("  %s\n", recv_buf);
    
    if(strcmp(recv_buf, "\nhave tne person") == 0){
        printf("  %s\n", recv_buf);
    } else if(strcmp(recv_buf, "\nzhuce sucess!") == 0){
    		printf("\n");
    		printf("\033[01;32m       %s\033[0m\n",recv_buf);
    		printf("请登录!\n");
    }
    printf("输入任意键继续！\n");
    getch();
}

int main(int argc, char **argv)
{
    int i;
    char ch;
    int ret;
    int conn_fd;
    int serv_port;
    struct sockaddr_in serv_addr;
    char recv_buf[1024]; 
    pthread_t thid1;  

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4507);
    inet_aton("127.0.0.1",&serv_addr.sin_addr);
    
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_fd < 0) {
        exit(1);
    }
    
    if(connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0) {
        puts(strerror(errno));
        exit(1);
    }
    
    pthread_mutex_init(&mutex, NULL);

    while(1){
        ch = my_page();
    	
    	switch(ch){
    	    case '1':
    	    	if((thid1 = my_denglu(conn_fd)) == 0){
    			    continue;
    			}
    			exit(0);
    			break;
    	    case '2':
    	    	my_zhuce(conn_fd);
    			break;
    		case '3':
    			my_guanli(conn_fd);
    	    case '0':
    	    	close(conn_fd);
    			return 0;
    	    default:
    	    	printf("\nplease input a right number!\n");
    	    	break;
    	}
    } 
    pthread_join(thid1, NULL);
    close(conn_fd);
    return 0;
}

