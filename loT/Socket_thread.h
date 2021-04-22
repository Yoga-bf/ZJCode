#ifndef Socket_Thread_
#define Socket_Thread_

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include "wrap.h"
#include "loT.h"

const int  N            = 1024;
struct shared_buff
{
    char                buff[N];
    bool                ready;
    int                 buff_len;
    mutex               mtx;
    // condition_variable  cv;
};

// #ifndef LOCAL_SHARED_
// extern shared_buff shared;
// #endif


void Socket_Send(int socketfd_send, loT & Slot, struct shared_buff *shared, int Type);
void Socket_Recv(int & socketfd_recv, loT & Slot, struct shared_buff *shared);
int get_length(char *buf);
void User_input(loT & lot, struct shared_buff *shared);
int Message_processing(char *message, int MesLen);

#endif