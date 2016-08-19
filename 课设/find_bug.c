/*************************************************************************
	> File Name: find_bug.c
	> Author:  toob
	> Mail: 1721627632@qq.com
	> Created Time: 2016年03月02日 星期三 18时16分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

#define MAX 1024  

int main(int argc, char **argv)
{
    FILE* fp;
    char buf[MAX];
    char software[MAX];
    char version[MAX];
    char find_software[MAX][MAX];
    char find_version[MAX][MAX];
    char find_data[MAX][MAX];
    char find_num[MAX];
    char *server = "localhost";
    char user[MAX];
    char password[MAX];
    char *database = "find_bug";
    size_t read;
    int i;
    int num = 0;
    int find_first[3][MAX];
    int find[3];
    int j,m;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (argc != 3) {
        printf("Use [name] [password]\n");
        return 1;
    }
    strcpy(user, argv[0]);
    strcpy(password, argv[1]);

    printf("software\t    version\t     error\n");

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    if (mysql_query(conn, "select * from name")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    res = mysql_use_result(conn);
    
    while ((row = mysql_fetch_row(res)) != NULL)  {
        strcpy(find_software[num], row[0]);
        strcpy(find_version[num], row[1]);
        strcpy(find_data[num], row[2]);
        if (find_version[num][0] == '<') {
            for (i=1, j=0; find_version[num][i] != '\0' && find_version[num][i] != '.'; i++, j++) {
                find_num[j] = find_version[num][i];
            }
            find_num[j] = '\0';
            find_first[0][num] = atoi(find_num);
            i++;
            for (j=0; find_version[num][i] != '\0' && find_version[num][i] != '.'; i++, j++) {
                find_num[j] = find_version[num][i];
            }
            find_num[j] = '\0';
            find_first[1][num] = atoi(find_num);
            if (find_version[num][i] == '\0'){
                find_first[2][num] = 0;
                num++;
                continue;
            }
            i++;
            for (j=0; find_version[num][i] != '\0' && find_version[num][i] != '.'; i++, j++) {
                find_num[j] = find_version[num][i];
            }
            find_num[j] = '\0';
            find_first[2][num] = atoi(find_num);
        }
        num++;
    }

    if (fopen("file_bug_txt","rb")) {
        system("rm file_bug_txt");
    }
    
    system("rpm -qa >> file_bug_txt");
    
    fp = fopen("file_bug_txt","rb");
    while ( fgets(buf, MAX, fp) != NULL ) {
        read = strlen(buf);
        for (i=read; i>0; i--) {
            if (buf[i] == '-') break;
        }
        bzero(software,MAX);
        bzero(version,MAX);
        buf[i] = '\0';
        strcpy(software, buf);
        while (buf[--i] != '-');
        strcpy(version, buf+i+1);
        software[i] = '\0';
            for (m=0, j=0; version[m] != '\0' && version[m] != '.'; m++, j++) {
                find_num[j] = version[m];
            }
            find_num[j] = '\0';
            find[0] = atoi(find_num);
            m++;
            for (j=0; version[m] != '\0' && version[m] != '.'; m++, j++) {
                find_num[j] = version[m];
            }
            find_num[j] = '\0';
            find[1] = atoi(find_num);
            if (version[m] == '\0'){
                find[2] = 0;
            } else {
                m++;
                for (j=0; version[m] != '\0' && version[m] != '.'; m++, j++) {
                    find_num[j] = version[m];
                }
                find_num[j] = '\0';
                find[2] = atoi(find_num);
            }
        for (i=0; i < num; i++) {
            if (strcmp(find_software[i], software) == 0) {
                if (find_version[i][0] != '<') {
                    if (strcmp(find_version[i], "null") == 0) {
                        printf("%-20s%s:\n",software, version);
                        printf("\033[31m%-40s%-40s\n\033[0m",find_software[i], find_data[i]);
                        break;
                    }
                    if (strcmp(find_version[i], version) == 0) {
                        printf("%-20s%s:\n",software, version);
                        printf("\033[31m%-20s%-20s%-40s\n\033[0m",find_software[i],find_version[i],find_data[i]);
                        break;
                    }
                } else if (find_version[i][0] == '<'){
                    if (find[0] < find_first[1][i]) {
                        printf("%-20s%s:\n",software, version);
                        printf("\033[31m%-20s%-20s%-40s\n\033[0m",find_software[i],find_version[i],find_data[i]);
                    } else if (find[0] == find_first[0][i]) {
                        if (find[1] < find_first[1][i]) {
                            printf("%-20s%s:\n",software, version);
                            printf("\033[31m%-20s%-20s%-40s\n\033[0m",find_software[i],find_version[i],find_data[i]);
                        } else if (find[1] == find_first[1][i]) {
                            if (find[2] <= find_first[2][i]) {
                                printf("%-20s%s:\n",software, version);
                                printf("\033[31m%-20s%-20s%-40s\n\033[0m",find_software[i],find_version[i],find_data[i]);
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    mysql_free_result(res);
    mysql_close(conn);
}
