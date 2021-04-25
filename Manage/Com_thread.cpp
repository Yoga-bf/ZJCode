#include <iostream>
#include "loT.h"
#include "wrap.h"
#include "Com_thread.h"

using namespace std;

void* Recv_loT_Signup(int server_socket_fd, loTDatabase* AllloT)
{
    int AcceptFd;
    while (1) {
        AcceptFd = Accept(server_socket_fd, NULL, NULL);

        char buffer[N] = {0};
        int size;

        size = Read(AcceptFd, buffer, N);

        loTMetadata SID;
        int k = MessageProcessing(buffer, size, SignUp, &SID);
        if (k == -1)
            continue;
        AllloT->mtx.lock();
        AllloT->loTDB.push_back(SID);
        AllloT->mtx.unlock();

    }
}

void* Com_with_loT(loTMetadata* myloT)
{
    
}