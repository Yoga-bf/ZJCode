#include "Socket_thread.h"
#include "buff_processing.h"
#include <cstring>

void Socket_Send(int & socketfd_send, loT & Slot, struct shared_buff *shared, int Type)
{

    if (socketfd_send <= -1)  {
        cout << "wrong socket" << endl;
        return;
    }
	if (Type < 0 || Type > 2) {
		cout << "wrong Type" << endl;
		return;
	}
	if (Type == 0){
		//sign up
		char sign_up[N] = {0};
		int n = buff_generate(sign_up, 0, NULL, 0, Slot);

		Write(socketfd_send, sign_up, n);
	}
	
	unique_lock<mutex> lck(shared->mtx);
	if (shared->buff[0] != 0) {
		Write(socketfd_send, shared->buff, shared->buff_len);
		cout << "send : " << shared->buff << endl;
		memset(shared->buff, 0, N);
		shared->buff_len = 0;
	}
	lck.unlock();

    // while(1) {
    //     unique_lock<mutex> lck(shared->mtx);
	// 	while (!shared->ready) {
	// 		shared->cv.wait(lck);
	// 	}	//wait for waking up
	// 	if (shared->buff[0] != 0) {
	// 		Write(socketfd_send, shared->buff, shared->buff_len);
    //         cout << "send : " << shared->buff << endl;
	// 		memset(shared->buff, 0, N);
	// 		shared->buff_len = 0;
	// 		shared->ready = false;
	// 	}
	// 	lck.unlock();
    // }
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
		// shared->cv.notify_all();
        Socket_Send(socketfd_recv, Slot, shared, 2);
	}
	 
}