	/*************************************************************************
    > File Name: my_ls.c
    > Author: zhanghaoran
    > Mail: chilumanxi@gmail.com 
    > Created Time: 2015年07月20日 星期一 09时45分49秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <malloc.h>

#define NO 0  //无参数
#define A 1   //ls -a
#define L 2   //ls -l
#define R 4   //ls -R
#define MAX   //一行显示最多


void my_err (const char *err_string, int line)
{
	fprintf(stderr, "line:%d  ",line);
	perror(err_string);
	exit(1);
}

void show_ls_l (struct stat buf)
{
        char buf_time[32];
	struct passwd *psd;
	struct group *grp;
	if(S_ISLNK(buf.st_mode)){
		printf("l");
	}else if(S_ISREG(buf.st_mode)){
		printf("-");
	}else if(S_ISDIR(buf.st_mode)){
		printf("d");
	}else if(S_ISCHR(buf.st_mode)){
		printf("c");
	}else if(S_ISBLK(buf.st_mode)){
		printf("b");
	}else if(S_ISFIFO(buf.st_mode)){
		printf("f");
	}else if(S_ISSOCK(buf.st_mode)){
		printf("s");
	}
	if(buf.st_mode & S_IRUSR){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IWUSR){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IXUSR){
		printf("x");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IRGRP){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IWGRP){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IXGRP){
		printf("x");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IROTH){
		printf("r");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IWOTH){
		printf("w");
	}else{
		printf("-");
	}
	if(buf.st_mode & S_IXOTH){
		printf("x");
	}else{
		printf("-");
	}
	printf(" ");
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%-2lu",buf.st_nlink);
    printf("%-6s",psd->pw_name);
	printf("%-6s",grp->gr_name);
    printf("%6ld",buf.st_size);
	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';
    printf("  %s",buf_time);
}

void show_ls_file(char *a, int aaa)
{
	printf("%s\n",a);
}

int show_ls (char *a, int aaa)
{
	DIR *dir;
	struct dirent *ptr;
	char filename[256][PATH_MAX+1];
	int count = 0, i = 0, len, j, k, sum = 0, x, y, m;
    int maxlen = 0;
	char temp[PATH_MAX+1];
	struct stat buf;
	char name[PATH_MAX];
	if ((dir = opendir(a)) == NULL) {
        my_err ("opendir", __LINE__);
	}
	while ((ptr = readdir(dir)) != NULL) {
		if (maxlen < strlen(ptr->d_name)) {
			maxlen = strlen(ptr->d_name);
		}
		count++;
	}
	if (count > 256) {
		my_err("more file", __LINE__);
	}
	closedir(dir);
	if ((dir = opendir(a)) == NULL) {
		my_err ("opendir", __LINE__);
	}
	while ((ptr = readdir(dir)) != NULL) {
		len = strlen(ptr->d_name);
		strcpy(filename[i],ptr->d_name);
        filename[i][len] = '\0';
		i++;
	}
    for ( j = 0; j < count-1; j++) {
		for (k = 0; k < count-1-j; k++) {
			if ( strcmp(filename[k],filename[k+1]) > 0) {
				strcpy(temp, filename[k+1]);
				strcpy(filename[k+1], filename[k]);
				strcpy(filename[k], temp);
			}
		}
	}
        switch(aaa)
       {
           case 0:
			   for (j = 0; j < i; j++) {
		   if ( filename[j][0] != '.') {
				if(sum > 80){
					printf("\n");
					sum = 0;
				}
				sum = sum + maxlen + 2;
				x=printf("%s ", filename[j]);
			    for(y=0;y<(maxlen+2-x);y++)
				    printf(" ");
			}
	   }
break;
           case 1:
            for (j = 0; j < i; j++) {
				if(sum > 80){
					printf("\n");
					sum = 0;
				}
				sum = sum + maxlen + 2;
			x=printf("%s ",filename[j]);
			for(y=0;y<(maxlen+2-x);y++)
				printf(" ");
		}
break;
            case 2:
            for (j = 0; j < i; j++) {
				if ( filename[j][0] != '.') {
					strcpy(name,a);
					strcat(name,"/");
					strcat(name,filename[j]);
					if (lstat(name,&buf) == -1) {
						my_err("lstat", __LINE__);
					}
					show_ls_l(buf);
					printf(" %s\n", filename[j]);
				}
		}
break;
           case 3:
            for (j = 0; j < i; j++) {
					strcpy(name,a);
					strcat(name,"/");
					strcat(name,filename[j]);
					if (lstat(name,&buf) == -1) {
						my_err("lstat", __LINE__);
					}
					show_ls_l(buf);
					printf(" %s\n", filename[j]);
		}
break;
		   case 4:
             m = 0;
             for (j = 0; j < i; j++) {
		         if ( filename[j][0] != '.') {
                             
			                strcpy(name,a);
					strcat(name,"/");
					strcat(name,filename[j]);
					strcpy(filename[j],name);
                                      
					if (lstat(filename[j],&buf) == -1) {
						my_err("lstat", __LINE__);
		         	}
				    if( S_ISDIR(buf.st_mode ) != 0){
						m++;
						show_ls(filename[j],R);
						//printf("%d1\n",m);
					}
				 }
			 }
			     //printf("%d2\n",m);
				 if(m == 0){
				    return 0;
				 }
				 for(j = 3; j < i; j++){
					if ( (filename[j][0] != '.') || ((filename[j][1] == '/') || filename[j][2] == '/' )) {
						if (lstat(filename[j],&buf) == -1) {
							my_err("lstat", __LINE__);
						}
					    if( S_ISDIR(buf.st_mode ) != 0){
							printf("\n%s:\n",filename[j]);
							show_ls(filename[j],0);
				 	    }
					}
				 }
			 break;
                case 5: m = 0;
             for (j = 0; j < i; j++) {
		         if ( filename[j][0] != '.') {
			                strcpy(name,a);
					strcat(name,"/");
					strcat(name,filename[j]);
					strcpy(filename[j],name);
					if (lstat(filename[j],&buf) == -1) {
						my_err("lstat", __LINE__);
		         	}
				    if( S_ISDIR(buf.st_mode ) != 0){
						m++;
						show_ls(filename[j],A+R);
						//printf("%d1\n",m);
					}
				 }
}

			     //printf("%d2\n",m);
				 if(m == 0){
				    return 0;
				 }
				 for(j = 3; j < i; j++){
					
						if (lstat(filename[j],&buf) == -1) {
							my_err("lstat", __LINE__);
						}
					    if( S_ISDIR(buf.st_mode ) != 0){
							printf("\n%s:\n",filename[j]);
							show_ls(filename[j],A);
				 	    }
					
}
 
	   }
	printf("\n");
	return 0;
}

void something1()
{
   show_ls("./",NO);
}

void something2(char **argv)
{
   struct stat buf2;
               if (argv[1][0] != '-') {
			lstat(argv[1], &buf2);
			if(S_ISDIR(buf2.st_mode)){
				show_ls(argv[1], NO);
			} else {
				show_ls_file(argv[1],NO);
			}
		} else {
			if (!strcmp(argv[1], "-a")) {
				show_ls("./", A);
			} else if (!strcmp(argv[1], "-l")) {
				show_ls("./", L);
			} else if (!(strcmp(argv[1], "-al") && strcmp(argv[1], "-la"))) {
				show_ls("./",A+L);
			} else if (!(strcmp(argv[1],"-R"))) {
				printf(".:\n");
				show_ls("./",NO);
				show_ls(".",R);
			}else if (!(strcmp(argv[1],"-aR"))) {
				printf(".:\n");
				show_ls("./",A);
				show_ls(".",R+A);
			}
		}
}

void something3(char **argv)
{
                struct stat buf2;
				char *buf=NULL;
				int i;
                if (!strcmp(argv[1], "-a")) {
			if(lstat(argv[2], &buf2) == -1) {
			    my_err("istat", __LINE__);
				exit(1);
			}
			if(S_ISDIR(buf2.st_mode)){
				show_ls(argv[2], A);
			} else {
				show_ls_file(argv[2],NO);
			}
		} else if (!strcmp(argv[1], "-l")) {
			if(lstat(argv[2], &buf2) == -1) {
			    my_err("istat", __LINE__);
			}
			if (S_ISDIR(buf2.st_mode)) {
				show_ls(argv[2], L);
			} else {
				show_ls_l(buf2);
				printf(" %s\n",argv[2]);
			}
		} else if (!(strcmp(argv[1], "-al") && strcmp(argv[1], "-la"))) {
			if(lstat(argv[2], &buf2) == -1) {
			    my_err("istat", __LINE__);
				exit(1);
			}
			if (S_ISDIR(buf2.st_mode)) {
				show_ls(argv[2], A+L);
			} else {
				show_ls_l(buf2);
				printf(" %s\n",argv[2]);
			}
	   } else if (!strcmp(argv[1],"-R")){
			if(lstat(argv[2], &buf2) == -1) {
			    my_err("istat", __LINE__);
				exit(1);
			}
			if (S_ISDIR(buf2.st_mode)) {
				if(!strcmp(argv[2],"./") ){
					printf("%s:\n",argv[2]);
					show_ls(argv[2],NO);
					show_ls(".",R);
				}else if(!strcmp(argv[2],"../")) {
					printf("%s:\n",argv[2]);
					show_ls(argv[2],NO);
					show_ls("..",R);
				} else {
			        printf("%s:\n",argv[2]);
				show_ls(argv[2],NO);
				show_ls(argv[2],R);
				}
			} else {
				printf(" %s\n",argv[2]);
			}
	   } else if (!(strcmp(argv[1],"-aR") && strcmp(argv[1],"-Ra"))){
			if(lstat(argv[2], &buf2) == -1) {
			    my_err("istat", __LINE__);
				exit(1);
			}
			if (S_ISDIR(buf2.st_mode)) {
				printf("%s:\n",argv[2]);
				show_ls(argv[2],A);
				show_ls(argv[2],A+R);
			} else {
				printf(" %s\n",argv[2]);
			}
	   }
}


int main (int argc, char **argv)
{
     switch(argc)
     {
         case 1:something1( );break; 
         case 2:something2(argv);break; 
         case 3:something3(argv);break; 
         default : printf("error"); break;
     }	
}
