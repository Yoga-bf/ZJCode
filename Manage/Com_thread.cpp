#include <iostream>
#include <cstring>
#include <list>
#include <thread>
#include "loT.h"
#include "wrap.h"
#include "Com_thread.h"
#include "pcap_send.h"

using namespace std;
int threadnum = 0;
mutex threadmux;

void* Recv_loT_Signup(int server_socket_fd, loTDatabase* AllloT)
{
    //Process the data sent by the loT
    int AcceptFd;
    //list<loTMetadata> loTs;
    loTMetadata loTs[100];
    while (1) {
        AcceptFd = Accept(server_socket_fd, NULL, NULL);

        char buffer[N] = {0};
        int size;

        size = Read(AcceptFd, buffer, N);

        int k = MessageProcessing(buffer, size, SignUp, &loTs[threadnum]);
        if (k == -1)
            continue;
        loTs[threadnum].socketfd = AcceptFd;
        //loTs.push_back(SID);
        AllloT->mtx.lock();
        AllloT->loTDB.push_back(loTs[threadnum]);
        AllloT->mtx.unlock();
        threadnum++;
        thread ComWithloT(Com_with_loT, &loTs[threadnum], &AllloT);
    }
}

void* Com_with_loT(loTMetadata* myloT, loTDatabase* AllloT)
{
    //Communication with IoT 
    int size;
    char buffer[N] = {0};
    while(1) {
        memset(buffer, 0, N*sizeof(char));
        size = Read(myloT->socketfd, buffer, N);

        if (size == 0) {
            cout << myloT->ID << " has been sign down" << endl;

            //send the sign down package
            memset(buffer, 0, N*sizeof(char));
            buffer[0] = SignDown;
            buffer[1] = myloT->type;
            memcpy(&buffer[2], myloT->ID, myloT->length);
            pcap_send(buffer, NULL, DST_IP, 1, (2+myloT->length));

            //delete the data of lot
            AllloT->mtx.lock();
            for (auto it = AllloT->loTDB.begin(); it != AllloT->loTDB.end(); it++) {
                if (it->ID == myloT->ID) {
                    it = AllloT->loTDB.erase(it);
                    break;
                }
            }
            AllloT->mtx.unlock();
            
        } else {
            loTMetadata slot;
            loTMetadata dlot;
            int k = MessageProcessing(buffer, size, Com, &slot, &dlot);
            if (k == -1 || slot.ID != myloT->ID) {
                cout << "the packet which loT send is wrong" << endl;
                continue;
            }
            myloT->buff_len = size;
            memcpy(myloT->buff, buffer, N);

            //whether the des lot is belonging of manage
            int desfd;
            AllloT->mtx.lock_shared();
            for (auto it = AllloT->loTDB.begin(); it != AllloT->loTDB.end(); it++) {
                if (it->ID == dlot.ID) {
                    k = -1;
                    desfd = it->socketfd;
                    break;
                }
            }
            AllloT->mtx.unlock_shared();

            if (k == -1) {
                //the lot is belong manage
                size = Write(desfd, buffer, size);
            } else {
                //the lot is not belong manage
                pcap_send(buffer, NULL, DST_IP, 1, size);
            }
        }
    }
}

void* Pcap_Receive()
{
    //Process the data sent by the switch
    pcap_receive();
}