#include "buff_mysocket_define.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void Socket_Send(char* buff, int socketfd_send)
{
    if (socketfd_send == -1)  {
        cout << "wrong socket" << endl;
        return;
    }

}

void  Socket_Recv(char* buff, int socketfd_recv)
{
    
}