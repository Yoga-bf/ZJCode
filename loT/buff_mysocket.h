#ifndef BUFF_MYSOCKET_DEFINE_H
#define BUFF_MYSOCKET_DEFINE_H

#include <thread>
#include <mutex>
#include "loT.h"

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT = loT(DEFAULT_TYPE));
void Socket_Send(int socketfd_send);
void Socket_Recv(int socketfd_recv);

#endif