#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define random_1(a,b) ((rand()%(b-a))+a)

char name_space[10] = {'0','1','2','3','4','5','6','7','8','9'};
MYSQL mysql;
char table_key[3] = "ID";
char table_match[6] = "VALUE";

int create_table(char* table_name, int m, int n, char* key, char* match);
int insert_data(char* table_name, char* key, char* match);
int create_table_top();
int create_table_top_V(char* table_name);
int create_table_top_V_NSI(char* table_name);
int create_table_top_V_NSI_AC(char* table_name);


int main()
{
    int k;
    if( NULL == mysql_init(&mysql) ){
        printf("error! %s\n", mysql_error(&mysql));
        return -1;
    }
    if ( NULL == mysql_real_connect(&mysql, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql));
        return -1;
    }
    printf("success connecting\n");
    k = create_table_top();
    if(k == -1)
        printf("erroe!\n");
    mysql_close(&mysql);
    return 0;
}

int create_table(char* table_name, int m, int n, char* key, char* match)
{
    int rc;
    MYSQL_RES* res = NULL;
    char *query_str = NULL;
    query_str = (char*)malloc(100);
    sprintf(query_str, "create table %s(%s char(%d) primary key, %s char(%d))", table_name, key, m, match, n);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return -1;
    }
    free(query_str);
    return 0;
}

int insert_data(char* table_name, char* key, char* match)
{
    int rc;
    MYSQL_RES* res = NULL;
    char *query_str = NULL;
    query_str = (char*)malloc(100);
    sprintf(query_str, "insert into %s values('%s', '%s')",table_name, key, match);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return -1;
    }
    free(query_str);
    return 0;
}

int create_table_top()
{
    int i,j,k;
    char* key = NULL;
    char* match = NULL;
    int key_length = 1;
    int match_length = 6;
    key = (char *)malloc(key_length+1);
    match = (char *)malloc(match_length+1);
    char table_name[6] = "Ecode";
    k = create_table(table_name, key_length, match_length, table_key, table_match);
    if( k == -1 ){
        printf("error in top!\n");
        free(key);
        free(match);
        return -1;
    }

    memset(key, 0, sizeof(key));
    memset(match, 0, sizeof(match));
    sprintf(key, "%c", name_space[1]);
    sprintf(match, "%s%c", table_name, name_space[1]);
    k = insert_data(table_name, key, match);
    if( k == -1 ){
        free(key);
        free(match);
        printf("error in top!\n");
        return -1;
    }
    k = create_table_top_V(match);
    if( k == -1 ) {
        free(key);
        free(match);
        return -1;
    }
    free(key);
    free(match);
    return 0;
}

int create_table_top_V(char* table_name)
{
    int i, i1, i2, i3, i4, i5, i6, i7, k;
    char* key = NULL;
    char* match = NULL;
    int key_length = 4;
    int match_length = 10;
    key = (char *)malloc(key_length+1);
    match = (char *)malloc(match_length+1);
    k = create_table(table_name, key_length, match_length, table_key, table_match);
    if( k == -1 ){
        printf("error in company!\n");
        free(key);
        free(match);
        return -1;
    }

        memset(key, 0, sizeof(key));
        memset(match, 0, sizeof(match));
        sprintf(key, "%c%c%c%c", name_space[0],name_space[0],name_space[6],name_space[4]);
        strcat(match, table_name);
        strcat(match, key);
        k = insert_data(table_name, key, match);
        if( k == -1 ){
            free(key);
            free(match);
            printf("error in company!\n");
            return -1;
        }
        k = create_table_top_V_NSI(match);
        if( k == -1 ){
            free(key);
            free(match);
            return -1;
        }
    free(key);
    free(match);
    return 0;
}

int create_table_top_V_NSI(char* table_name)
{
    int i, i1, i2, i3, i4, i5, i6, k;
    char* key = NULL;
    char* match = NULL;
    int key_length = 6;
    int match_length = 16;
    key = (char *)malloc(key_length+1);
    match = (char *)malloc(match_length+1);
    k = create_table(table_name, key_length, match_length, table_key, table_match);
    if( k == -1 ){
        free(key);
        free(match);
        printf("error in type!\n");
        return -1;
    }
    for(i = 0; i < 500; i++)
    {
        memset(key, 0, sizeof(key));
        memset(match, 0, sizeof(match));
        i1 = random_1(1,10);
        i2 = random_1(1,10);
        i3 = random_1(1,10);
        i4 = random_1(1,10);
        i5 = random_1(1,10);
        i6 = random_1(1,10);
        sprintf(key, "%c%c%c%c%c%c", name_space[i1],name_space[i2],name_space[i3],name_space[i4],name_space[i5],name_space[i6]);
        strcat(match, table_name);
        strcat(match, key);
        k = insert_data(table_name, key, match);
        if( k == -1 ){
            printf("error in type!\n");
            free(key);
            free(match);
            return -1;
        }
        k = create_table_top_V_NSI_AC(match);
        if( k == -1 ){
            free(key);
            free(match);
            return -1;
        }
    }
    free(key);
    free(match);
    return 0;
}

int create_table_top_V_NSI_AC(char* table_name)
{
    int k;
    char* key = NULL;
    char* match = NULL;
    int key_length = 6;
    int match_length = 15;
    key = (char *)malloc(key_length+1);
    match = (char *)malloc(match_length+1);
    k = create_table(table_name, key_length, match_length, table_key, table_match);
    if( k == -1 ){
        printf("error in object!\n");
        free(key);
        free(match);
        return -1;
    }
    free(key);
    free(match);
    return 0;
}