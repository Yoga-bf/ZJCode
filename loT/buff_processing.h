#ifndef BUFF_MYSOCKET_DEFINE_H
#define BUFF_MYSOCKET_DEFINE_H


#include "loT.h"

int buff_generate(char * buff, int Type, char * message, int n, loT & SloT, loT DloT = loT(DEFAULT_TYPE));

#endif