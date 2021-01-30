#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>

#include "buff_mysocket.h"


void Socket_Send(int socketfd_send)
{
    if (socketfd_send == -1)  {
        cout << "wrong socket" << endl;
        return;
    }
    while(1) {
        //std::lock();
    }
}

void  Socket_Recv(int socketfd_recv)
{
    
}

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT)
{
    if (Type == 0) {
        buff[0] = SloT.GetType();

        string SID;
        int SID_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();

        SID.copy(buff, SID_length, 1);
        buff[SID_length + 1] = '\0';

        return SID_length + 1;
    }
    else if (Type == 1) {
        buff[0] = SloT.GetType();

        string SID, DID;
        int SID_length, DID_length, total_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();
        DID = DloT.GetID();
        DID_length = DloT.GetID_length();

        SID.copy(buff, SID_length, 1);
        buff[SID_length + 1] = DloT.GetType();
        DID.copy(buff, DID_length, 2 + SID_length);

        total_length = SID_length + DID_length;

        memcpy(&buff[total_length + 2], message, n);
        return n + 2 + total_length;
    }
    else {
        cout << "wrong Type" << endl;
        return -1;
    }
}