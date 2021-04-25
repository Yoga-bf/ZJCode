#include <iostream>
#include <cstring>
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
        SID.socketfd = AcceptFd;
        AllloT->mtx.lock();
        AllloT->loTDB.push_back(SID);
        AllloT->mtx.unlock();

    }
}

void* Com_with_loT(loTMetadata* myloT, loTDatabase* AllloT)
{
    int size;
    char buffer[N] = {0};
    while(1) {
        memset(buffer, 0, N*sizeof(char));
        size = Read(myloT->socketfd, buffer, N);

        if (size == 0) {
            cout << myloT->ID << " has been sign down" << endl;
            //the package of sign down
            AllloT->mtx.lock();
            for (auto it = AllloT->loTDB.begin(); it != AllloT->loTDB.end(); it++) {
                if (it->ID == myloT->ID) {
                    it = AllloT->loTDB.erase(it);
                    break;
                }
            }
            AllloT->mtx.unlock();
        } else {
            myloT->buff_len = size;
            memcpy(myloT->buff, buffer, N);
            //how to deal with this package
            //may be the des is not belong the manage, otherwise.
            //may be i need a function to send the message to the lot of the manage.
        }
    }
}