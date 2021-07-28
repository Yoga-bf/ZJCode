#include "server.h"
#include "wrap.h"
#include "data_processing.h"
#include <time.h>
#include <sys/time.h>
#define hhhhh 1
#define EPC_char_length 24
#define Ecode_char_length 17
#define OID_char_length 16
/*
int main(int argc, char **argv)
{

    if( NULL == mysql_init(&mysql_EPC) ){
        printf("error! %s\n", mysql_error(&mysql_EPC));
        return -1;
    }

    if( NULL == mysql_init(&mysql_Ecode) ){
        printf("error! %s\n", mysql_error(&mysql_Ecode));
        return -1;
    }

	if( NULL == mysql_init(&mysql_OID) ){
        printf("error! %s\n", mysql_error(&mysql_OID));
        return -1;
    }

    if ( NULL == mysql_real_connect(&mysql_EPC, "localhost", "root", "hengheng", "EPC", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_EPC));
        return -1;
    }
    printf("success epc connect EPC!\n");

    if ( NULL == mysql_real_connect(&mysql_Ecode, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_Ecode));
        return -1;
    }
    printf("success Ecode connect Ecode!\n");

	if ( NULL == mysql_real_connect(&mysql_OID, "localhost", "root", "hengheng", "OID", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_OID));
        return -1;
    }
    printf("success Ecode connect OID!\n");

	int i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	socklen_t cliaddr_len;
	struct sockaddr_in cliaddr, servaddr;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	bzero(&cliaddr,sizeof(cliaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	Listen(listenfd, 20);
	
	maxfd = listenfd;
	maxi = -1;
	memset(client, 0, sizeof(client));
	for (i = 0; i < FD_SETSIZE; i++)
		client[i].client_status = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	for( ; ; )
	{
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if (nready < 0)
			perr_exit("select error");
			
		if (FD_ISSET(listenfd, &rset))
		{
			cliaddr_len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
			
			printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),ntohs(cliaddr.sin_port));
			
			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i].client_status < 0) {
					client[i].client_status = connfd;
					strcpy(client[i].client_ip, inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)));
					break;
				}
			
			if (i == FD_SETSIZE) {
				fputs("too many clients\n", stderr);
				exit(1);
			}
			
			FD_SET(connfd, &allset);
			
			if (connfd > maxfd)
				maxfd = connfd;
			if (i > maxi)
				maxi = i;
			if (--nready == 0)
				continue;
		}
		
		for (i = 0; i <= maxi; i++)
		{
			if ( (sockfd = client[i].client_status) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset))
			{
				if ( (n = Read(sockfd, buf, MAXLINE)) == 0)
				{
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i].client_status = -1;
					memset(client[i].client_ip, 0, sizeof(client[i].client_ip));
					printf("offline!\n");
				}
				else
				{//process the data
			int lot_packet;
			for(lot_packet=0; lot_packet<22; lot_packet++){
				printf(" %02x", buf[lot_packet]);
				if((lot_packet+1)%16==0)
					printf("\n");
			}
                    Extract_data(i, buf);
                    write(connfd, "192.168.109.222", n);
				}
				
				if (--nready == 0)
					break;
			}
		}
	}
}
*/

#define BUFFER_SIZE 1024
					
int main()
{
	if( NULL == mysql_init(&mysql_EPC) ){
        printf("error! %s\n", mysql_error(&mysql_EPC));
        return -1;
    }

    if( NULL == mysql_init(&mysql_Ecode) ){
        printf("error! %s\n", mysql_error(&mysql_Ecode));
        return -1;
    }

	if( NULL == mysql_init(&mysql_OID) ){
        printf("error! %s\n", mysql_error(&mysql_OID));
        return -1;
    }

    if ( NULL == mysql_real_connect(&mysql_EPC, "localhost", "root", "hengheng", "EPC", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_EPC));
        return -1;
    }
    printf("success epc connect EPC!\n");

    if ( NULL == mysql_real_connect(&mysql_Ecode, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_Ecode));
        return -1;
    }
    printf("success Ecode connect Ecode!\n");

	if ( NULL == mysql_real_connect(&mysql_OID, "localhost", "root", "hengheng", "OID", 0, NULL, 0)){
        printf("connect error ! %s", mysql_error(&mysql_OID));
        return -1;
    }
    printf("success Ecode connect OID!\n");
	printf("wait for SDN connecting\n");
	//goto test;
	char listen_addr_str[] = "0.0.0.0";

    size_t listen_addr = inet_addr(listen_addr_str);

    int port = 8000;

    int server_socket, client_socket;

	int i;

    struct sockaddr_in server_addr, client_addr;

    socklen_t addr_size;

    unsigned char buffer[BUFFER_SIZE] = {0};

	int str_length;

	server_socket = socket(PF_INET, SOCK_STREAM, 0);

	bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = INADDR_ANY;

    server_addr.sin_port = htons(port);

    server_addr.sin_addr.s_addr = listen_addr;

	if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("绑定失败\n");
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        printf("监听失败\n");
        return 1;
    }

    printf("success create TCP server\n");

	int result_action = 0;

	struct timeval start;
	struct timeval stop;

    addr_size = sizeof(client_addr);
	while(1){
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addr_size);
	printf("%d success connect\n", client_socket);
	//while(1){
		str_length = read(client_socket, buffer, BUFFER_SIZE);
test:
		
		
		//strcpy(buffer, "32313130303634313133373336313233343536");
		//gettimeofday(&start, NULL);
		//str_length = 1;     //测试查询时间
   		if (str_length == 0)    //读取数据完毕关闭套接字
		{
			close(client_socket);
			printf("连接已经关闭: %d \n", client_socket);
			//break;
		} 
		else 
		{
			char* buff = NULL;
			buff = (char *)calloc(1, 200);
			char* real_buff = NULL;
			real_buff = (char *)calloc(1,200);
			buff_change(buffer, real_buff);
			printf("it send: \n%s\n",real_buff);
			printf("buffer_length is %d, buffer_strlen is %d\n", str_length, (int)strlen(buffer));

			//result_action = Extract_data(0, buffer, buff);
			result_action = deal_packet(real_buff, buff);

			printf("buff is %s\n",buff);
			//write(client_socket, "192.168.109.99", 14);
			if(result_action == -1){
				printf("something is wrong\n");
			}
			else if(result_action == -2){
				printf("inquire wrong\n");
			}
			if(buff[0] != '0'){
				printf("ip is : %s\n", buff);
				printf("%d\n", (int)strlen(buff));
				send(client_socket, buff, strlen(buff), 0);

				//gettimeofday(&stop, NULL);
				//printf("Use Time: %ld ms\n",stop.tv_sec * 1000  + stop.tv_usec/1000  - start.tv_sec * 1000  - start.tv_usec/1000 );
				// while(1){

				// }  //测试查询时间
				
				//write(client_socket, buff, strlen(buff));
			}
		}
		close(client_socket);
	//}
	}

}

void buff_change(unsigned char* buff, char* return_buff)
{
	int n = 0;
	n = strlen(buff);
	int i;
	char a,b;
	int p,q;
	int m;
	int length = 0;
	if(buff[3] == '0'){
		length = 2 * EPC_char_length;
	}
	if(buff[3] == '1'){
		length = 2 * Ecode_char_length;
	}
	if(buff[3] == '2'){
		length = 2 * OID_char_length;
	}
	for(i = 0; i < (4+length)/2; i++){
		a = buff[2*i];
		b = buff[2*i+1];
		p = a - 48;
		q = b - 48;
		m = p * 16 + q;
		return_buff[i] = m;
		
	}
	strcat(return_buff, &buff[4+length]);
	
}

int deal_packet(unsigned char* buff, char* return_char)
{
	unsigned char* buf = NULL;
    buf = (unsigned char*)calloc(1, MAXLINE);
    strcpy(buf, buff);

    MYSQL mysql;
    MYSQL_RES *res;
	MYSQL_ROW row;

    int inquire_result = 0;
    int rc;
    char* query_str = NULL;
    query_str = (char*)calloc(1, 150);

	if(buf[1] == '0'){

		char* head = NULL;
        char* company = NULL;
        char* type = NULL;
        char* object = NULL;

		int head_p = 2;  //position
		int company_p = head_p + EPC_head;
		int type_p = company_p + EPC_company;
		int object_p = type_p + EPC_type;

		head = (char*)calloc(1, EPC_head + 1);
        company = (char*)calloc(1, EPC_company + 1);
        type = (char*)calloc(1, EPC_type + 1);
        object = (char*)calloc(1, EPC_object + 1);

		strncpy(head, &buf[head_p], EPC_head);
		strncpy(company, &buf[company_p], EPC_company);
		strncpy(type, &buf[type_p], EPC_type);
		strncpy(object, &buf[object_p], EPC_object);
        
		if(buf[0] == '0'){

			int ip_length = 0;
			ip_length = strlen(buf) - EPC_char_length - 2;

			char* ip_host = NULL;
			ip_host = (char*)calloc(1, ip_length + 1);

			int ip_p = object_p + EPC_object;

			strncpy(ip_host, &buf[ip_p], ip_length);
			printf("ip is %s\n",ip_host);

			sprintf(query_str, "insert into EPC%s%s%s values('%s', '%s')", head, company, type, object, ip_host);
			
			EPC_up_requery:
			rc = mysql_real_query(&mysql_EPC, query_str, strlen(query_str));

            if (0 != rc) {
                printf("%d\n", rc);
                if(2013 == mysql_errno(&mysql_EPC)){
                    if ( NULL == mysql_real_connect(&mysql_EPC, "localhost", "root", "hengheng", "EPC", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_EPC));
                        return -1;
                    }
                    goto EPC_up_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_EPC));
                return -1;
            }

		}

		else if(buf[0] == '1'){

			sprintf(query_str, "delete from EPC%s%s%s where ID = '%s'", head, company, type, object);

			EPC_down_requery:
            rc = mysql_real_query(&mysql_EPC, query_str, strlen(query_str));
            if (0 != rc) {
                if(2013 == mysql_errno(&mysql_EPC)){
                    if ( NULL == mysql_real_connect(&mysql_EPC, "localhost", "root", "hengheng", "EPC", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_EPC));
                        return -1;
                    }
                    goto EPC_down_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_EPC));
                return -1;
            }
		}
		else if(buf[0] == '2'){

			sprintf(query_str, "select VALUE from EPC%s%s%s where ID = '%s'", head, company, type, object);
			printf("inquire is\n%s\n",query_str);

			EPC_inquire_requery:
            rc = mysql_real_query(&mysql_EPC, query_str, strlen(query_str));
            if (0 != rc) {
                if(2013 == mysql_errno(&mysql_EPC)){
                    if ( NULL == mysql_real_connect(&mysql_EPC, "localhost", "root", "hengheng", "EPC", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_EPC));
                        return -1;
                    }
                    goto EPC_inquire_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_EPC));
                return -1;
            }
            inquire_result = -2;
            res = mysql_store_result(&mysql_EPC);
            while(row=mysql_fetch_row(res)){
                inquire_result = 1;
                strcat(return_char, row[0]);
            }
            mysql_free_result(res);
		}
	}

	else if(buf[1] == '1'){

		char* Version = NULL;
        char* NSI = NULL;
        char* AC = NULL;
        char* IC = NULL;

		Version = (char*)calloc(1, Ecode_Version + 1);
        NSI = (char*)calloc(1, Ecode_NSI + 1);
        AC = (char*)calloc(1, Ecode_AC + 1);
        IC = (char*)calloc(1, Ecode_IC + 1);

		int Version_p = 2;
		int NSI_p = Version_p + Ecode_Version;
		int AC_p = NSI_p + Ecode_NSI;
		int IC_p = AC_p + Ecode_AC;

		strncpy(Version, &buf[Version_p], Ecode_Version);
		strncpy(NSI, &buf[NSI_p], Ecode_NSI);
		strncpy(AC, &buf[AC_p], Ecode_AC);
		strncpy(IC, &buf[IC_p], Ecode_IC);

		if(buf[0] == '0'){

			int ip_length = 0;
			ip_length = strlen(buf) - Ecode_char_length - 2;

			char* ip_host = NULL;
			ip_host = (char*)calloc(1, ip_length + 1);

			int ip_p = IC_p + Ecode_IC;

			strncpy(ip_host, &buf[ip_p], ip_length);
			printf("ip is %s\n",ip_host);

			sprintf(query_str, "insert into Ecode%s%s%s values('%s', '%s')", Version, NSI, AC, IC, ip_host);

			Ecode_up_requery:
			rc = mysql_real_query(&mysql_Ecode, query_str, strlen(query_str));
            if (0 != rc) {

                if(2013 == mysql_errno(&mysql_Ecode)){
                    if ( NULL == mysql_real_connect(&mysql_Ecode, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_Ecode));
                        return -1;
                    }
                    goto Ecode_up_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_Ecode));
                return -1;
            }
		
		}
		else if(buf[0] == '1'){

			sprintf(query_str, "delete from Ecode%s%s%s where ID = '%s'", Version, NSI, AC, IC);

			Ecode_down_requery:
			rc = mysql_real_query(&mysql_Ecode, query_str, strlen(query_str));
            if (0 != rc) {
                if(2013 == mysql_errno(&mysql_Ecode)){
                    if ( NULL == mysql_real_connect(&mysql_Ecode, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_Ecode));
                        return -1;
                    }
                    goto Ecode_down_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_Ecode));
                return -1;
            }
		}
		else if(buf[0] == '2'){

			sprintf(query_str, "select VALUE from Ecode%s%s%s where ID = '%s'", Version, NSI, AC, IC);

			Ecode_inquire_requery:
			rc = mysql_real_query(&mysql_Ecode, query_str, strlen(query_str));
            if (0 != rc) {
                if(2013 == mysql_errno(&mysql_Ecode)){
                    if ( NULL == mysql_real_connect(&mysql_Ecode, "localhost", "root", "hengheng", "Ecode", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_Ecode));
                        return -1;
                    }
                    goto Ecode_inquire_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_Ecode));
                return -1;
            }

            inquire_result = -2;
            res = mysql_store_result(&mysql_Ecode);
            while(row=mysql_fetch_row(res)){
                inquire_result = 1;
                strcat(return_char, row[0]);
            }
            mysql_free_result(res);
		}
		
	}
	else if(buf[1] == '2'){

		char* company = NULL;
        char* object = NULL;

		company = (char*)calloc(1, OID_company + 1);
        object = (char*)calloc(1, OID_object + 1);

		int company_p = 2;
		int object_p = 2 + OID_company;

		strncpy(company, &buf[company_p], OID_company);
		strncpy(object, &buf[object_p], OID_object);

		if(buf[0] == '0'){

			int ip_length = 0;
			ip_length = strlen(buf) - OID_char_length - 2;

			char* ip_host = NULL;
			ip_host = (char*)calloc(1, ip_length + 1);

			int ip_p = object_p + OID_object;

			strncpy(ip_host, &buf[ip_p], ip_length);
			printf("ip is %s\n",ip_host);

			sprintf(query_str, "insert into OID%s values('%s', '%s')", company, object, ip_host);
			OID_up_requery:
			rc = mysql_real_query(&mysql_OID, query_str, strlen(query_str));
            if (0 != rc) {

                if(2013 == mysql_errno(&mysql_OID)){
                    if ( NULL == mysql_real_connect(&mysql_OID, "localhost", "root", "hengheng", "OID", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_OID));
                        return -1;
                    }
                    goto OID_up_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_OID));
                return -1;
            }
		}
		else if(buf[0] == '1'){
			sprintf(query_str, "delete from OID%s where ID = '%s'", company, object);
			OID_down_requery:
			rc = mysql_real_query(&mysql_OID, query_str, strlen(query_str));
            if (0 != rc) {

                if(2013 == mysql_errno(&mysql_OID)){
                    if ( NULL == mysql_real_connect(&mysql_OID, "localhost", "root", "hengheng", "OID", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_OID));
                        return -1;
                    }
                    goto OID_down_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_OID));
                return -1;
            }
		}
		else if(buf[0] == '2'){
			sprintf(query_str, "select VALUE from OID%s where ID = '%s'", company, object);
			OID_inquire_requery:
			rc = mysql_real_query(&mysql_OID, query_str, strlen(query_str));
            if (0 != rc) {

                if(2013 == mysql_errno(&mysql_OID)){
                    if ( NULL == mysql_real_connect(&mysql_OID, "localhost", "root", "hengheng", "OID", 0, NULL, 0)){
                        printf("connect error ! %s", mysql_error(&mysql_OID));
                        return -1;
                    }
                    goto OID_inquire_requery;
                }
                printf("mysql_real_query(): %s\n", mysql_error(&mysql_OID));
                return -1;
            }

            inquire_result = -2;
            res = mysql_store_result(&mysql_OID);
            while(row=mysql_fetch_row(res)){
                inquire_result = 1;
                strcat(return_char, row[0]);
            }
            mysql_free_result(res);
		}
	}

}
