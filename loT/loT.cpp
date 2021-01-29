#include "loT.h"


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