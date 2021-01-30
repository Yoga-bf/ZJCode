#include <thread>
#include <cstring>
#include "loT.h"
#include "ID.h"
#include "buff_processing.h"

const char SERVER_IP[] = "127.0.0.1";
const int  PORT        = 8000;

int main()
{
    shared_buff shared;
    memset(shared.buff, 0, N);
    shared.ready = false;
    shared.buff_len = 0;
    loT lot(h1_ID);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd_write);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd_read);
    return 0;
}