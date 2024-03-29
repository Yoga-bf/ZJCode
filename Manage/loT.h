#ifndef LOT_H
#define LOT_H
#include </usr/include/c++/9/shared_mutex>
#include <string>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>

#include "mynet.h"

using namespace std;

//const int LOT_TYPE_LENGTH[3] = {};
//用 map 表示 长度与种类的关系

static map<int, char> length_type = {{24, '0'}, {17, '1'}, {16, '2'}};
const char DEFAULT_TYPE = '9';
const static int MAXIDLength = 30;


class loT
{
private:
    string ID;
    char Type;
    int ID_length;
public:
    // int socketfd_read;
    // int socketfd_send;
    int socketfd;
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

struct loTMetadata
{
    /* data */
    char    ID[MAXIDLength];
    char    type;
    unsigned int     length;     //the length of ID
    int     socketfd;
    char    buff[N];
    int     buff_len;
};

struct loTDatabase
{
    vector<loTMetadata> loTDB;
    mutable shared_mutex mtx;
};

extern loTDatabase AllloT;
#endif