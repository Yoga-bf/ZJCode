#include <thread>
#include <cstring>
#include "loT.h"
#include "pcap_send.h"
#include "wrap.h"
#include "net.h"

const int  PORT = 8000;
const char Myip[] = "127.0.0.1";

int main()
{
    int server_socket_fd;
    struct sockaddr_in ser_addr;

    SocketMake(&ser_addr, &server_socket_fd, PORT, Myip);

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
        
        

    }
    return 0;
}