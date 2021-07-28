#include "IoT.h"
#include "buff_processing.h"
#include <cstring>

loT::loT()
{
    ID            = "nullptr";
    Type          = DEFAULT_TYPE;
    ID_length     = 7;
    // socketfd_send = -1;
    // socketfd_read = -1;
    socketfd      = -1;
}

loT::loT(string id)
{
    this->ID = id;
    this->ID_length = id.length();
    auto type = length_type.find(id.length());
    // socketfd_send = -1;
    // socketfd_read = -1;
    socketfd = -1;
    if (type != length_type.end()){
        this->Type = type->second;
        cout << "success create loT" << endl;
        cout << "ID is : " << this->ID << endl;
    } else {
        cout << "wrong ID: fail to create loT" << endl;
    }
    
}

loT::loT(char type)
{
    ID = "nullptr";
    Type = type;
    ID_length = 7;
    // socketfd_send = -1;
    // socketfd_read = -1;
    socketfd = -1;
}

loT::loT(const loT & cp)
{
    this->ID = cp.ID;
    this->Type = cp.Type;
    this->ID_length = cp.Type;
    // socketfd_send = -1;
    // socketfd_read = -1;
    socketfd = -1;
}

loT & loT::operator=(const loT & cp)
{
    if (this == &cp)
        return *this;
    ID = cp.ID;
    Type = cp.Type;
    ID_length = ID.length();
    // socketfd_send = -1;
    // socketfd_read = -1;
    socketfd = -1;
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



