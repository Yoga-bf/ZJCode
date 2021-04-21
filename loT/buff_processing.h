#ifndef BUFF_MYSOCKET_DEFINE_H
#define BUFF_MYSOCKET_DEFINE_H


#include "loT.h"
const int  N            = 1024;

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT = loT(DEFAULT_TYPE));
struct shared_buff
{
    char                buff[N];
    bool                ready;
    int                 buff_len;
    mutex               mtx;
    condition_variable  cv;
};

// #ifndef LOCAL_SHARED_
// extern shared_buff shared;
// #endif


void Socket_Send(int & socketfd_send, loT & Slot, struct shared_buff *shared);
void Socket_Recv(int & socketfd_recv, loT & Slot, struct shared_buff *shared);


#endif