#include <sys/types.h>
#include <string>
#include <iostream>
#include <cstring>
#include "buff_processing.h"


int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT)
{
    if (Type == 0) {
        buff[0] = SloT.GetType();

        string SID;
        int SID_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();

        SID.copy(buff, SID_length, 1);
        buff[SID_length + 1] = '\0';

        return SID_length + 1;
    }
    else if (Type == 1) {
        buff[0] = SloT.GetType();

        string SID, DID;
        int SID_length, DID_length, total_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();
        DID = DloT.GetID();
        DID_length = DloT.GetID_length();

        SID.copy(buff, SID_length, 1);
        buff[SID_length + 1] = DloT.GetType();
        DID.copy(buff, DID_length, 2 + SID_length);

        total_length = SID_length + DID_length;

        memcpy(&buff[total_length + 2], message, n);
        return n + 2 + total_length;
    }
    else {
        cout << "wrong Type" << endl;
        return -1;
    }
}

void Socket_Send(int & socketfd_send, loT & Slot, struct shared_buff *shared)
{

    if (socketfd_send == -1)  {
        cout << "wrong socket" << endl;
        return;
    }

	char sign_up[N] = {0};
	int n = buff_generate(sign_up, 0, NULL, 0, Slot);

	Write(socketfd_send, sign_up, n);
	//sign up

    while(1) {
        unique_lock<mutex> lck(shared->mtx);
		while (!shared->ready) {
			shared->cv.wait(lck);
		}	//wait for waking up
		if (shared->buff[0] != 0) {
			Write(socketfd_send, shared->buff, shared->buff_len);
            cout << "send : " << shared->buff << endl;
			memset(shared->buff, 0, N);
			shared->buff_len = 0;
			shared->ready = false;
		}
		lck.unlock();
    }
}

void Socket_Recv(int & socketfd_recv, loT & Slot, struct shared_buff *shared)
{
    char buffer[N] = {0};
	int n;
	while(1){
		n = Read(socketfd_recv, buffer, N);

		//need a function to deal with buffer
        cout << "recv : " << buffer << endl; 
		unique_lock<mutex> lck(shared->mtx);
		shared->ready = true;
		shared->buff_len = n;
		strncpy(shared->buff, buffer, n);
        lck.unlock();
		shared->cv.notify_all();
        
	}
	 
}