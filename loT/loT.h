#include <string>
#include <iostream>
using namespace std;

//const int LOT_TYPE_LENGTH[3] = {};
//用 map 表示 长度与种类的关系
class loT
{
private:
    string ID;
    int Type;
    int ID_length;
public:
    loT();
    loT(string id, int Type);
    loT(const loT & cp);
    loT & operator=(const loT & cp);
    ~loT();
};

loT::loT()
{
    ID = "nullptr";
    Type = -1;
    ID_length = 7;
}

loT::loT(string id, int Type)
{
    this->ID = id;
    this->Type = Type;
    this->ID_length = id.length();
    cout << "success create loT" << endl;
    cout << "ID is : " << this->ID << endl;
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