#ifndef BUFF_MYSOCKET_DEFINE_H
#define BUFF_MYSOCKET_DEFINE_H


#include "loT.h"

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT = loT(DEFAULT_TYPE));
const static char SignUp = '0';
const static char SignDown = '1';
const static char Com = '2';


#endif