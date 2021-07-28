#include <thread>
#include <cstring>
#include <unistd.h>
#include "loT.h"
#include "ID.h"
#include "Socket_thread.h"
#include "buff_processing.h"

const char SERVER_IP[] = "192.168.109.238";
const int  PORT        = 8080;

int main()
{
    shared_buff lotshared;
    shared_buff *shared = &lotshared;
    memset(lotshared.buff, 0, N);
    lotshared.ready = false;
    lotshared.buff_len = 0;

    loT lot(h1_ID);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd);
    
    Socket_Send(lot.socketfd, lot, shared, SignM);  //Sign up
    
    //Socket_Send(lot.socketfd, lot, shared, SendM);
    
    thread socketrecv(Socket_Recv, std::ref(lot.socketfd), std::ref(lot), shared);
    
    User_input(lot, shared);
    
    socketrecv.join();

    return 0;
}
