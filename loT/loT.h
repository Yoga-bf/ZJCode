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

loT::loT()
{
    ID = "nullptr";
    Type = '-1';
    ID_length = 7;
}

loT::loT(string id)
{
    this->ID = id;
    this->ID_length = id.length();
    auto type = length_type.find(id.length());
    if (type != length_type.end()){
        this->Type = type->second;
        cout << "success create loT" << endl;
        cout << "ID is : " << this->ID << endl;
    } 
    else{
        cout << "wrong ID: fail to create loT" << endl;
    }
    
}

loT::loT(char type)
{
    ID = "nullptr";
    Type = type;
    ID_length = 7; 
}

loT::loT(const loT & cp)
{
    this->ID = cp.ID;
    this->Type = cp.Type;
    this->ID_length = cp.Type;
}

loT & loT::operator=(const loT & cp)
{
    if (this == &cp)
        return *this;
    ID = cp.ID;
    Type = cp.Type;
    ID_length = ID.length();
}

loT::~loT()
{

}