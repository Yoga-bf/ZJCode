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
    
    Socket_Send(lot.socketfd, lot, shared, 0);  //Sign up

    //thread socketsend(Socket_Send, std::ref(lot.socketfd), std::ref(lot), shared);
    thread socketrecv(Socket_Recv, std::ref(lot.socketfd), std::ref(lot), shared);
    //socketsend.join();
    
    loT DesloT();
    while(1){
        string id;
        char Type;
        cout << "Destination ID is: " << endl;
        cin >> id;
        cout << "Type is: " << endl;
        cin >> Type;
        auto TType = length_type.find(id.length());
        if (TType == length_type.end()) {
            cout << "id is wrong" << endl;
            continue;
        } else if (TType->second != Type) {
            cout << "id or type is wrong" << endl;
            continue;
        }
        char buffer[N] = {0};
        cout << "input the message: " << endl;
        cin >> buffer;
        //buff_generate(buffer, )
    }

    socketrecv.join();

    return 0;
}