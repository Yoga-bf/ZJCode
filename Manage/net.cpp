#include "net.h"
#include "wrap.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

void SocketMake(struct sockaddr_in * ser_addr, int * server_socket_fd, int PORT, const char *Myip)
{
    *server_socket_fd = Socket(AF_INET, SOCK_STREAM, 0);
    int addr_len = sizeof(ser_addr);
    ser_addr->sin_family = AF_INET;
    ser_addr->sin_port = htons(PORT);
    ser_addr->sin_addr.s_addr =  htonl(INADDR_ANY);
    Bind(*server_socket_fd, (struct sockaddr*)&ser_addr, addr_len);
    Listen(*server_socket_fd, 10);
}

int MessageProcessing(char *message, int size, char Type, char *SID, char *DID)
{
    //Type is the type of package
    char type = message[0];
    if (type != Type) {
        cout << "wrong the type of package" << endl;
        return -1;
    }
    

}