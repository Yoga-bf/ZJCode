#include <sys/types.h>
#include <string>
#include <iostream>
#include <cstring>
#include "buff_processing.h"


int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT)
{
    if (Type == SignM) {
        buff[0] = SloT.GetType();

        string SID;
        int SID_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();

        SID.copy(buff, SID_length, 1);
        buff[SID_length + 1] = '\0';
        cout << "ge buff is " << endl;

        return SID_length + 1;
    }
    else if (Type == SendM) {
        buff[0] = DloT.GetType();

        string SID, DID;
        int SID_length, DID_length, total_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();
        DID = DloT.GetID();
        DID_length = DloT.GetID_length();

        DID.copy(buff, DID_length, 1);
        buff[DID_length + 1] = SloT.GetType();
        SID.copy(buff, SID_length, 2 + DID_length);

        total_length = SID_length + DID_length;

        memcpy(&buff[total_length + 2], message, n);
        return n + 2 + total_length;
    }
    else {
        cout << "wrong Type" << endl;
        return -1;
    }
}

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, string Did, char DIDType)
{
    if (Type == SignM) {
        buff[0] = SloT.GetType();

        string SID;
        int SID_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();

        SID.copy(&buff[1], SID_length, 0);
        buff[SID_length + 1] = '\0';
        cout << "ge buff is " << endl;

        return SID_length + 1;
    }
    else if (Type == SendM) {
        
        buff[0] = DIDType;

        string SID;
        int SID_length, DID_length, total_length;

        SID = SloT.GetID();
        SID_length = SloT.GetID_length();
        DID_length = Did.length();
        
        Did.copy(&buff[1], DID_length, 0);
        buff[DID_length + 1] = SloT.GetType();
        
        SID.copy(&buff[DID_length + 2], SID_length, 0);
        
        total_length = SID_length + DID_length;
        cout << total_length << endl;
        memcpy(&buff[total_length + 2], message, n);
        return n + 2 + total_length;
    }
    else {
        cout << "wrong Type" << endl;
        return -1;
    }
}