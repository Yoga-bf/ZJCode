#ifndef BUFF_MYSOCKET_DEFINE_H
#define BUFF_MYSOCKET_DEFINE_H

#include "loT.h"

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT = loT('-1'));
void Socket_Send(char* buff, int socketfd_send);
void  Socket_Recv(char* buff, int socketfd_recv);

#endif