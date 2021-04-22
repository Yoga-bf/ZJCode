#include "Socket_thread.h"
#include "buff_processing.h"
#include <cstring>

void Socket_Send(int socketfd_send, loT & Slot, struct shared_buff *shared, int Type)
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
		sign_up[0] = SignUp;
		int n = buff_generate(&sign_up[1], SignM, NULL, 0, Slot);
		cout << sign_up << endl;
		Write(socketfd_send, sign_up, n);
		
	}
	
	if (shared->buff[0] != 0) {
		Write(socketfd_send, shared->buff, shared->buff_len);
		memset(shared->buff, 0, N);
		shared->buff_len = 0;
	}

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
		//n = recv(socketfd_recv, buffer, N, 0);

		//need a function to deal with buffer
        cout << "recv : " << buffer << endl; 
		//unique_lock<mutex> lck(shared->mtx);
		shared->mtx.lock();
		shared->ready = true;
		shared->buff_len = n;
		buffer[0] = '1';
		
		strncpy(shared->buff, buffer, n);
		// shared->cv.notify_all();
        Socket_Send(socketfd_recv, Slot, shared, 2);
		//lck.unlock();
		shared->mtx.unlock();
	}
	 
}

int get_length(char *buf)
{
    int i = 0;
    while (buf[i++] != 0){}
    return i-1;
}

void User_input(loT & lot, struct shared_buff *shared)
{
	while(1){
        string id;
		string IDType;
        char Type;

        cout << "Destination ID is: " << endl;
        getline(cin, id);
        cout << "Type is: " << endl;
		getline(cin, IDType);
        Type = *((char *)IDType.c_str());
        auto TType = length_type.find(id.length());

        if (TType == length_type.end()) {
            cout << "id is wrong" << endl;
            continue;
        } else if (TType->second != Type) {
            cout << "id or type is wrong" << endl;
            continue;
        }

        //char message[N] = {0};
		string message;
		char buffer[N] = {0};
		buffer[0] = '2';

        cout << "input the message: " << endl;
        getline(cin, message);

        //int MessageLen = get_length(message);
		
        buff_generate(&buffer[1], SendM, (char *)message.c_str(), message.length(), lot, id, Type);
		shared->mtx.lock();
        //unique_lock<mutex> lck(shared->mtx, std::adopt_lock);
		
        shared->ready = true;
		shared->buff_len = get_length(buffer);
		strncpy(shared->buff, buffer, shared->buff_len);
        Socket_Send(lot.socketfd, lot, shared, SendM);
		cout << "success send" << endl;
		shared->mtx.unlock();
		
    }
}