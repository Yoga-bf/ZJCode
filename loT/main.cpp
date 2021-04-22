#include <thread>
#include <cstring>
#include "loT.h"
#include "ID.h"
#include "Socket_thread.h"
#include "buff_processing.h"

const char SERVER_IP[] = "127.0.0.1";
const int  PORT        = 8000;

int main()
{
    shared_buff lotshared;
    shared_buff *shared = &lotshared;
    memset(lotshared.buff, 0, N);
    lotshared.ready = false;
    lotshared.buff_len = 0;

    loT lot(h1_ID);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd);
    //lot.SocketMake(SERVER_IP, PORT, lot.socketfd);
    
    //thread socketsend(Socket_Send, std::ref(lot.socketfd), std::ref(lot), shared);
    thread socketrecv(Socket_Recv, std::ref(lot.socketfd), std::ref(lot), shared);
    //socketsend.join();
    socketrecv.join();

    while(1){

    }

    return 0;
}