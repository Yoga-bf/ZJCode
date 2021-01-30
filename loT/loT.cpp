#include "loT.h"
#include "buff_processing.h"
#include <cstring>

loT::loT()
{
    ID = "nullptr";
    Type = DEFAULT_TYPE;
    ID_length = 7;
    socketfd_write = -1;
    socketfd_read = -1;
}

loT::loT(string id)
{
    this->ID = id;
    this->ID_length = id.length();
    auto type = length_type.find(id.length());
    socketfd_write = -1;
    socketfd_read = -1;
    if (type != length_type.end()){
        this->Type = type->second;
        cout << "success create loT" << endl;
        cout << "ID is : " << this->ID << endl;
    } 
    else{
        cout << "wrong ID: fail to create loT" << endl;
    }
    
}

loT::loT(char type)
{
    ID = "nullptr";
    Type = type;
    ID_length = 7;
    socketfd_write = -1;
    socketfd_read = -1;
}

loT::loT(const loT & cp)
{
    this->ID = cp.ID;
    this->Type = cp.Type;
    this->ID_length = cp.Type;
    socketfd_write = -1;
    socketfd_read = -1;
}

loT & loT::operator=(const loT & cp)
{
    if (this == &cp)
        return *this;
    ID = cp.ID;
    Type = cp.Type;
    ID_length = ID.length();
    socketfd_write = -1;
    socketfd_read = -1;
    return *this;
}

void loT::SocketMake(const char *server_ip, int SPort, int & socketfd)
{
    struct sockaddr_in servaddr;

    socketfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, (const char *)server_ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(SPort);
	
	Connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	cout << "success connect server" << endl;

}

loT::~loT()
{

}

void Socket_Send(int socketfd_send, loT & Slot, struct shared_buff shared)
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
        unique_lock<mutex> lck(shared.mtx);
		while (!shared.ready) {
			shared.cv.wait(lck);
		}	//wait for waking up
		if (shared.buff[0] != 0) {
			Write(socketfd_send, shared.buff, shared.buff_len);
			memset(shared.buff, 0, N);
			shared.buff_len = 0;
			shared.ready = false;
		}
		lck.unlock();
    }
}

void Socket_Recv(int socketfd_recv, loT & Slot, struct shared_buff shared)
{
    char buffer[N] = {0};
	int n;
	while(1){
		n = Read(socketfd_recv, buffer, N);

		//need a function to deal with buffer

		unique_lock<mutex> lck(shared.mtx);
		shared.ready = true;
		shared.buff_len = n;
		strncpy(shared.buff, buffer, n);
		shared.cv.notify_all();
	}
	 
}

