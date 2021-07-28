#include <thread>
#include <cstring>
#include "loT.h"
#include "pcap_send.h"
#include "wrap.h"
#include "mynet.h"
#include <netinet/in.h>
#include "Com_thread.h"

const int  PORT = 8080;
const char Myip[] = "127.0.0.1";

loTDatabase AllloT;

int main()
{
    int server_socket_fd;
    struct sockaddr_in ser_addr;

    //SocketMake(&ser_addr, &server_socket_fd, PORT, Myip);
    server_socket_fd = Socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addr_len = sizeof(ser_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    ser_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
    Bind(server_socket_fd, (struct sockaddr*)&ser_addr, addr_len);
    Listen(server_socket_fd, 10);

    thread loTSocket(Recv_loT_Signup, server_socket_fd);
    thread ComWithSwitch(Pcap_Receive);
    
    loTSocket.join();
    ComWithSwitch.join();
    return 0;
}
