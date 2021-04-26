#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "mynet.h"
#include "wrap.h"
#include "loT.h"


using namespace std;

void SocketMake(struct sockaddr_in * ser_addr, int * server_socket_fd, int PORT, const char *Myip)
{
    *server_socket_fd = Socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addr_len = sizeof(ser_addr);
    ser_addr->sin_family = AF_INET;
    ser_addr->sin_port = htons(PORT);
    ser_addr->sin_addr.s_addr =  htonl(INADDR_ANY);
    Bind(*server_socket_fd, (struct sockaddr*)&ser_addr, addr_len);
    Listen(*server_socket_fd, 10);
}

int MessageProcessing(char *message, int size, char Type, struct loTMetadata *SloT, struct loTMetadata *DloT)
{
    //Type is the type of package
    cout << "lot send " << message << endl;
    char type = message[0];
    if (type != Type) {
        cout << "wrong the type of package" << endl;
        return -1;
    }

    if (type == Com) {
        char DesType = message[1];
        auto typelength = TypeLength.find(DesType);
        if (typelength == TypeLength.end()) {
            cout << "Com: wrong DID" << endl;
            return -1;
        }
        DloT->length = typelength->second;
        memcpy(DloT->ID, &message[2], DloT->length);


        char SouType = message[2+DloT->length];
        typelength = TypeLength.find(SouType);
        if (typelength == TypeLength.end()) {
            cout << "Com: wrong SID" << endl;
            return -1;
        }
        SloT->length = typelength->second;
        memcpy(SloT->ID, &message[3+DloT->length], SloT->length);
        return 0;
    }

    if (type == SignUp) {
        char SouType = message[1];
        memset(SloT->ID, 0, sizeof(char)*MAXIDLength);
        SloT->type = SouType;
        auto typelength = TypeLength.find(SouType);
        if (typelength == TypeLength.end()) {
            cout << "sign up: wrong SID" << endl;
            return -1;
        }
        SloT->length = typelength->second;
        cout << SloT->length << endl;
        memcpy(SloT->ID, &message[2], (size_t)SloT->length);
    }
    return 1;
}