#ifndef Socket_Thread_
#define Socket_Thread_

#include <string>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "wrap.h"
#include "loT.h"

const int  N            = 1024;
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