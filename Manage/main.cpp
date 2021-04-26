#include <thread>
#include <cstring>
#include "loT.h"
#include "pcap_send.h"
#include "wrap.h"
#include "net.h"
#include <netinet/in.h>
#include "Com_thread.h"

const int  PORT = 8000;
const char Myip[] = "127.0.0.1";
loTDatabase AllloT;

int main()
{
    int server_socket_fd;
    struct sockaddr_in ser_addr;

    SocketMake(&ser_addr, &server_socket_fd, PORT, Myip);

    thread loTSocket(Recv_loT_Signup, server_socket_fd, &AllloT);
    thread ComWithSwitch(Pcap_Receive);
    
    loTSocket.join();
    ComWithSwitch.join();
    return 0;
}