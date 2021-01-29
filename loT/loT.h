#ifndef LOT_H
#define LOT_H

#include <string>
#include <iostream>
#include <map>
using namespace std;

//const int LOT_TYPE_LENGTH[3] = {};
//用 map 表示 长度与种类的关系

static map<int, char> length_type = {{24, '0'}, {17, '1'}, {16, '2'}};

class loT
{
private:
    string ID;
    char Type;
    int ID_length;
public:
    loT();
    loT(string id);
    loT(char type);
    loT(const loT & cp);
    loT & operator=(const loT & cp);
    string GetID() {return this->ID;};
    char GetType() {return this->Type;};
    int GetID_length() {return this->ID_length;};
    ~loT();
};

#endif
