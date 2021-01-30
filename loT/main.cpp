#include <thread>
#include "loT.h"
#include "ID.h"
#include "buff_mysocket.h"

const char SERVER_IP[] = "127.0.0.1";
const int  PORT        = 8000;

int main()
{
    char buff[N] = {0};
    loT lot(h1_ID);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd_write);
    lot.SocketMake(SERVER_IP, PORT, lot.socketfd_read);
    return 0;
}