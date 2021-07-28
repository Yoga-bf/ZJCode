#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define EPC_head 2
#define EPC_company 7
#define EPC_type 6
#define EPC_object 9
#define EPC_bit_length 12

#define Ecode_Version 1
#define Ecode_NSI 4
#define Ecode_AC 6
#define Ecode_IC 6
#define Ecode_bit_length 9

#define OID_company 8
#define OID_object 8
#define OID_bit_length 9

int Extract_data(int num, unsigned char* buff, char* return_char);
void DatatoHex_int(int* data, int n, char* Hex);
void DatatoTen_int(int* data, int n, char* Ten);
void EPC_data(unsigned char* buff, char* head, char* company, char* type, char* object);
void Ecode_data(unsigned char* buff, char* Version,  char* NSI, char* AC, char* IC);
void OID_data(unsigned char* buff, char* company_id, char* object_id);
