#include "data_processing.h"
#include "server.h"

int Extract_data(int num, unsigned char* buff, char* return_char)
{   // return 0 represent success, -1 represent error

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

    if( buf[0] == '0')
    {
        // sign up
        if ( buf[1] == '0')
        {
            //EPC
            char* head = NULL;
            char* company = NULL;
            char* type = NULL;
            char* object = NULL;
            char* ip_host = NULL;
            int ip_length = 0;
            ip_length = strlen(buf) - EPC_bit_length - 2;

            head = (char*)calloc(1, EPC_head + 1);
            company = (char*)calloc(1, EPC_company + 1);
            type = (char*)calloc(1, EPC_type + 1);
            object = (char*)calloc(1, EPC_object + 1);
            ip_host = (char*)calloc(1, ip_length + 1);

            EPC_data(buf, head, company, type, object);
            printf("ip is %s\n",ip_host);
            EPC_up_requery:
            strncpy(ip_host, &buf[EPC_bit_length+2], ip_length);

            printf("%s\n%s\n%s\n%s\n", head, company, type, object);
            sprintf(query_str, "insert into EPC%s%s%s values('%s', '%s')", head, company, type, object, ip_host);

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

            free(head);
            free(company);
            free(type);
            free(object);
        }
        else if( buf[1] == '1')
        {

            char* Version = NULL;
            char* NSI = NULL;
            char* AC = NULL;
            char* IC = NULL;
            char* ip_host = NULL;
            int ip_length = 0;
            ip_length = strlen(buf) - Ecode_bit_length - 2;


            Version = (char*)calloc(1, Ecode_Version + 1);
            NSI = (char*)calloc(1, Ecode_NSI + 1);
            AC = (char*)calloc(1, Ecode_AC + 1);
            IC = (char*)calloc(1, Ecode_IC + 1);
            ip_host = (char*)calloc(1, ip_length + 1);

            strncpy(ip_host, &buf[Ecode_bit_length+2], ip_length);

            Ecode_data(buf, Version, NSI, AC, IC);
            Ecode_up_requery:
            sprintf(query_str, "insert into Ecode%s%s%s values('%s', '%s')", Version, NSI, AC, IC, ip_host);

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

            free(Version);
            free(NSI);
            free(AC);
            free(IC);
            free(ip_host);
        }

        else if( buf[1] == '2')
        {

            char* company = NULL;
            char* object = NULL;
            char* ip_host = NULL;
            int ip_length = 0;
            ip_length = strlen(buf) - OID_bit_length - 2;

            company = (char*)calloc(1, OID_company + 1);
            object = (char*)calloc(1, OID_object + 1);
            ip_host = (char*)calloc(1, ip_length + 1);

            strncpy(ip_host, &buf[Ecode_bit_length+2], ip_length);

            OID_data(buf, company, object);
            OID_up_requery:
            sprintf(query_str, "insert into OID%s values('%s', '%s')", company, object, ip_host);
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
    }

    if( buf[0] == '1')
    {
        // sign down
        if( buf[1] == '0')
        {
            //EPC
            char* head = NULL;
            char* company = NULL;
            char* type = NULL;
            char* object = NULL;

            head = (char*)malloc(3);
            company = (char*)malloc(8);
            type = (char*)malloc(7);
            object = (char*)malloc(10);

            EPC_data(buf, head, company, type, object);

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

            free(head);
            free(company);
            free(type);
            free(object);
        }

        else if( buf[1] == '1')
        {
            char* Version = NULL;
            char* NSI = NULL;
            char* AC = NULL;
            char* IC = NULL;

            Version = (char*)calloc(1, Ecode_Version + 1);
            NSI = (char*)calloc(1, Ecode_NSI + 1);
            AC = (char*)calloc(1, Ecode_AC + 1);
            IC = (char*)calloc(1, Ecode_IC + 1);

            Ecode_data(buf, Version, NSI, AC, IC);
            Ecode_down_requery:
            sprintf(query_str, "delete from Ecode%s%s%s where ID = '%s'", Version, NSI, AC, IC);

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

            free(Version);
            free(NSI);
            free(AC);
            free(IC);
        }

        else if(buf[1] == '2')
        {
            char* company = NULL;
            char* object = NULL;

            company = (char*)calloc(1, OID_company + 1);
            object = (char*)calloc(1, OID_object + 1);

            OID_data(buf, company, object);
            OID_down_requery:
            sprintf(query_str, "delete from OID%s where ID = '%s'", company, object);
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
    }

    if( buf[0] == '2')
    {    
   //inquire
        if( buf[1] == '0')
        {
		printf("it is EPC\n");
            //EPC
            char* head = NULL;
            char* company = NULL;
            char* type = NULL;
            char* object = NULL;

            head = (char*)calloc(1,3);
            company = (char*)calloc(1,8);
            type = (char*)calloc(1,7);
            object = (char*)calloc(1,10);

            EPC_data(buf, head, company, type, object);

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


            free(head);
            free(company);
            free(type);
            free(object);
        }

        else if( buf[1] == '1')
        {
            char* Version = NULL;
            char* NSI = NULL;
            char* AC = NULL;
            char* IC = NULL;

            Version = (char*)calloc(1, Ecode_Version + 1);
            NSI = (char*)calloc(1, Ecode_NSI + 1);
            AC = (char*)calloc(1, Ecode_AC + 1);
            IC = (char*)calloc(1, Ecode_IC + 1);

            Ecode_data(buf, Version, NSI, AC, IC);
            Ecode_inquire_requery:
            sprintf(query_str, "selete VALUE from Ecode%s%s%s where ID = '%s'", Version, NSI, AC, IC);

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

            free(Version);
            free(NSI);
            free(AC);
            free(IC);
        }

        else if(buf[1] == '2')
        {
            char* company = NULL;
            char* object = NULL;

            company = (char*)calloc(1, OID_company + 1);
            object = (char*)calloc(1, OID_object + 1);

            OID_data(buf, company, object);
            OID_inquire_requery:
            sprintf(query_str, "selete VALUE from OID%s where ID = '%s'", company, object);
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

    free(query_str);
    return 0;

}

void DatatoHex_int(int* data, int n, char* Hex)
{
    int j;
    char a;
    for(j = 0; j < n; j++)
    {
        if (data[j] < 10 && data[j] >= 0)
        {
            Hex[j] = data[j] + 48;
        }
        else{
            Hex[j] = data[j] + 55;
            }
    }
    Hex[j] = '\0';
}

void DatatoTen_int(int* data, int n, char* Ten)
{
    int j;
    char a;
    for(j = 0; j < n; j++)
    {
        if(data[j] < 10 && data[j] >= 0)
        {
            Ten[j] = data[j] + 48;
        }
        else{
            Ten[j] = 48;
        }
    }
    Ten[j] = '\0';
}

void EPC_data(unsigned char* buff, char* head, char* company, char* type, char* object)
{
    unsigned char* buf = NULL;
    buf = (unsigned char*)malloc(MAXLINE);
    memset(buf, 0, sizeof(buf));
    strcpy(buf, buff);
    unsigned int data_int[10];
    int i,j;

    data_int[0] = (unsigned int)(buf[2] >> 4);
    data_int[1] = (unsigned int)(buf[2] & 15);
    DatatoHex_int(data_int, EPC_head, head);

    data_int[0] = (unsigned int)(buf[3] >> 4);
    data_int[1] = (unsigned int)(buf[3] & 15);
    data_int[2] = (unsigned int)(buf[4] >> 4);
    data_int[3] = (unsigned int)(buf[4] & 15);
    data_int[4] = (unsigned int)(buf[5] >> 4);
    data_int[5] = (unsigned int)(buf[5] & 15);
    data_int[6] = (unsigned int)(buf[6] >> 4);
    DatatoHex_int(data_int, EPC_company, company);

    data_int[0] = (unsigned int)(buf[6] & 15);
    data_int[1] = (unsigned int)(buf[7] >> 4);
    data_int[2] = (unsigned int)(buf[7] & 15);
    data_int[3] = (unsigned int)(buf[8] >> 4);
    data_int[4] = (unsigned int)(buf[8] & 15);
    data_int[5] = (unsigned int)(buf[9] >> 4);
    DatatoHex_int(data_int, EPC_type, type);

    data_int[0] = (unsigned int)(buf[9] & 15);
    data_int[1] = (unsigned int)(buf[10] >> 4);
    data_int[2] = (unsigned int)(buf[10] & 15);
    data_int[3] = (unsigned int)(buf[11] >> 4);
    data_int[4] = (unsigned int)(buf[11] & 15);
    data_int[5] = (unsigned int)(buf[12] >> 4);
    data_int[6] = (unsigned int)(buf[12] & 15);
    data_int[7] = (unsigned int)(buf[13] >> 4);
    data_int[8] = (unsigned int)(buf[13] & 15);
    DatatoHex_int(data_int, EPC_object, object);

    free(buf);
}

void Ecode_data(unsigned char* buff, char* Version, char* NSI, char* AC, char* IC)
{
    unsigned char* buf = NULL;
    buf = (unsigned char*)malloc(MAXLINE);
    memset(buf, 0, sizeof(buf));
    strcpy(buf, buff);
    unsigned int data_int[10];
    int i,j;

    Version[0] = buff[2];

    data_int[0] = (unsigned int)(buf[3] >> 4);
    data_int[1] = (unsigned int)(buf[3] & 15);
    data_int[2] = (unsigned int)(buf[4] >> 4);
    data_int[3] = (unsigned int)(buf[4] & 15);
    DatatoTen_int(data_int, Ecode_NSI, NSI);

    data_int[0] = (unsigned int)(buf[5] >> 4);
    data_int[1] = (unsigned int)(buf[5] & 15);
    data_int[2] = (unsigned int)(buf[6] >> 4);
    data_int[3] = (unsigned int)(buf[6] & 15);
    data_int[4] = (unsigned int)(buf[7] >> 4);
    data_int[5] = (unsigned int)(buf[7] & 15);
    DatatoTen_int(data_int, Ecode_AC, AC);

    data_int[0] = (unsigned int)(buf[8] >> 4);
    data_int[1] = (unsigned int)(buf[8] & 15);
    data_int[2] = (unsigned int)(buf[9] >> 4);
    data_int[3] = (unsigned int)(buf[9] & 15);
    data_int[4] = (unsigned int)(buf[10] >> 4);
    data_int[5] = (unsigned int)(buf[10] & 15);
    DatatoTen_int(data_int, Ecode_IC, IC);

    free(buf);
}

void OID_data(unsigned char* buff, char* company_id, char* object_id)
{
    unsigned char* buf = NULL;
    buf = (unsigned char*)malloc(MAXLINE);
    memset(buf, 0, sizeof(buf));
    strcpy(buf, buff);
    unsigned int data_int[10];
    int i,j;

    printf("hello\n");

    data_int[0] = (unsigned int)(buf[2] >> 4);
    data_int[1] = (unsigned int)(buf[2] & 15);
    data_int[2] = (unsigned int)(buf[3] >> 4);
    data_int[3] = (unsigned int)(buf[3] & 15);
    data_int[4] = (unsigned int)(buf[4] >> 4);
    data_int[5] = (unsigned int)(buf[4] & 15);
    data_int[6] = (unsigned int)(buf[5] >> 4);
    data_int[7] = (unsigned int)(buf[5] & 15);
    DatatoTen_int(data_int, OID_company, company_id);

    data_int[0] = (unsigned int)(buf[7] >> 4);
    data_int[1] = (unsigned int)(buf[7] & 15);
    data_int[2] = (unsigned int)(buf[8] >> 4);
    data_int[3] = (unsigned int)(buf[8] & 15);
    data_int[4] = (unsigned int)(buf[9] >> 4);
    data_int[5] = (unsigned int)(buf[9] & 15);
    data_int[6] = (unsigned int)(buf[10] >> 4);
    data_int[7] = (unsigned int)(buf[10] & 15);
    DatatoTen_int(data_int, OID_object, object_id);

    printf("%s\n%s\n", company_id, object_id);

    int ttttt = 1;
    free(buf);
}
