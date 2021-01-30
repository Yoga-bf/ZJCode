#ifndef LOT_H
#define LOT_H

#include <string>
#include <iostream>
#include <map>
#include <thread>
#include <mutex>
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
    int socketfd_write;
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

struct 
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    char            buff[N];
} shared = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};


#endif