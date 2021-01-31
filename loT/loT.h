#ifndef LOT_H
#define LOT_H

#include <string>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "wrap.h"
using namespace std;

//const int LOT_TYPE_LENGTH[3] = {};
//用 map 表示 长度与种类的关系

static map<int, char> length_type = {{24, '0'}, {17, '1'}, {16, '2'}};
const char DEFAULT_TYPE = '9';
const int  N            = 1024;

class loT
{
private:
    string ID;
    char Type;
    int ID_length;
public:
    int socketfd_read;
    int socketfd_send;
    loT();
    loT(string id);
    loT(char type);
    loT(const loT & cp);
    loT & operator=(const loT & cp);
    string GetID() {return this->ID;};
    char GetType() {return this->Type;};
    int GetID_length() {return this->ID_length;};
    void SocketMake(const char *server_ip, int SPort, int & socketfd);
    ~loT();
};


struct shared_buff
{
    char                buff[N];
    bool                ready;
    int                 buff_len;
    mutex               mtx;
    condition_variable  cv;
};

// #ifndef LOCAL_SHARED_
// extern shared_buff shared;
// #endif


void Socket_Send(int & socketfd_send, loT & Slot, struct shared_buff *shared);
void Socket_Recv(int & socketfd_recv, loT & Slot, struct shared_buff *shared);

#endif