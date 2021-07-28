#include <thread>
#include <iostream>
#include <cstring>
#include <list>
#include <unistd.h>

#include "loT.h"
#include "wrap.h"
#include "Com_thread.h"
#include "pcap_send.h"
#include "mynet.h"

using namespace std;
int threadnum = 0;
loTMetadata loTs[100];

void* Recv_loT_Signup(int server_socket_fd)
{
    //Process the data sent by the loT
    int AcceptFd;
    //list<loTMetadata> loTs;

    while (1) {
        cout << "wait for connect " << endl;
        AcceptFd = Accept(server_socket_fd, NULL, NULL);

        char buffer[N] = {0};
        int size;

        size = Read(AcceptFd, buffer, N);
        

        int k = MessageProcessing(buffer, size, SignUp, &loTs[threadnum]);
        if (k == -1)
            continue;

        loTs[threadnum].socketfd = AcceptFd;
        //loTs.push_back(SID);
        AllloT.mtx.lock();
        AllloT.loTDB.push_back(loTs[threadnum]);
        AllloT.mtx.unlock();
        thread ComWithloT(Com_with_loT, &loTs[threadnum]);
        threadnum++;
        ComWithloT.detach();
    }

    
}

void* Com_with_loT(loTMetadata* myloT)
{
    //Communication with IoT 
    int size;
    char buffer[N] = {0};
    cout << "Com with loT " << myloT->ID << endl;

    //sign in
    buffer[0] = '0';
    buffer[1] = myloT->type;
    memcpy(&buffer[2], myloT->ID, myloT->length);
    size = myloT->length + 2;
    pcap_send(buffer, NULL, DST_IP, 1, size);
    
    while(1) {
        memset(buffer, 0, N*sizeof(char));
        cout << "wait for the message from lot" << endl;
        size = Read(myloT->socketfd, buffer, N);
        cout << "lot send something" << endl;
        if (size <= 0) {
            cout << myloT->ID << " has been sign down" << endl;

            //send the sign down package
            memset(buffer, 0, N*sizeof(char));
            buffer[0] = SignDown;
            buffer[1] = myloT->type;
            memcpy(&buffer[2], myloT->ID, myloT->length);
            pcap_send(buffer, NULL, DST_IP, 1, (2+myloT->length));

            //delete the data of lot
            AllloT.mtx.lock();
            for (auto it = AllloT.loTDB.begin(); it != AllloT.loTDB.end(); it++) {
                if ((strcmp(it->ID, myloT->ID) == 0)) {
                    it = AllloT.loTDB.erase(it);
                    break;
                }
            }
            AllloT.mtx.unlock();
            break;

        } else {
            loTMetadata slot;
            loTMetadata dlot;
            //something wrong with this function
            int k = MessageProcessing(buffer, size, Com, &slot, &dlot);
            //if (k == -1 || slot.ID != myloT->ID) {
            if (k == -1 || (strcmp(slot.ID, myloT->ID) != 0)) {
                cout << "messageprocess is " << k << endl;
                cout << "slot is " << slot.ID << endl;
                cout << "dlot is " << dlot.ID << endl;
                cout << "the packet which loT send is wrong" << endl;
                continue;
            }
            myloT->buff_len = size;
            memcpy(myloT->buff, buffer, N);
            cout << myloT->ID << " send " << buffer << endl;
            //whether the des lot is belonging of manage
            int desfd;
            AllloT.mtx.lock_shared();
            for (auto it = AllloT.loTDB.begin(); it != AllloT.loTDB.end(); it++) {
                if (strcmp(it->ID, dlot.ID) == 0) {
                    k = -1;
                    desfd = it->socketfd;
                    break;
                }
            }
            AllloT.mtx.unlock_shared();

            if (k == -1) {
                //the lot is belong manage
                size = Write(desfd, buffer, size);
            } else {
                //the lot is not belong manage
                //while(1){
                    cout << "send " << buffer << endl;
                    pcap_send(buffer, NULL, DST_IP, 10000, size);
                    //break;
                //}
                
            }
        }
    }
    return NULL;
}

void* Pcap_Receive()
{
    //Process the data sent by the switch
    int k = pcap_receive();
    return NULL;
}