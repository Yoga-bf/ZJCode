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
		return;
	}
	
	if (shared->buff[0] != 0) {
		Write(socketfd_send, shared->buff, shared->buff_len);
		memset(shared->buff, 0, N);
		shared->buff_len = 0;
	}
}

void Socket_Recv(int & socketfd_recv, loT & Slot, struct shared_buff *shared)
{
    char buffer[N] = {0};
	int n;
	while(1){
		n = Read(socketfd_recv, buffer, N);
        cout << "recv : " << buffer << endl;

		int k = Message_processing(buffer, get_length(buffer));
		if (k == -1)
			continue;
		cout << "recv buff is " << buffer << endl;
		shared->mtx.lock();
		shared->ready = true;
		shared->buff_len = n;
		
		strncpy(shared->buff, buffer, n);
        Socket_Send(socketfd_recv, Slot, shared, 2);
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

int Message_processing(char *message, int MesLen)
{
	if (message[0] != Com) {
		cout << "wrong message" << endl;
		return -1;
	}
	char SID[N] = {0}, DID[N] = {0};
	char SType, DType;
	int SLength = 0, DLength = 0;
	DType = message[1];
	for (std::map<int, char>::iterator it = length_type.begin(); it != length_type.end(); it++) {
		if (it->second == DType) {
			DLength = it->first;
		}
	}
	if (DLength == 0) {
		cout << "Des Type is wrong" << endl;
		return -1;
	}
	SType = message[2+DLength];
	for (std::map<int, char>::iterator it = length_type.begin(); it != length_type.end(); it++) {
		if (it->second == SType) {
			SLength = it->first;
		}
	}
	if (SLength == 0) {
		cout << "Sou Type is wrong" << endl;
		return -1;
	}

	char mmessage[N] = {0};
	mmessage[0] = Com;
	mmessage[1] = SType;

	memcpy(&mmessage[1], &message[2+DLength], SLength+1);
	memcpy(&mmessage[2+SLength], &message[1], DLength+1);
	memcpy(message, mmessage, 3+DLength+SLength);

	return 0;
}