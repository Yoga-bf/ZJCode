#ifndef Net_
#define Net_

#include <map>


const static char SignUp = '0';
const static char SignDown = '1';
const static char Com = '2';

const int N = 1024;
void SocketMake(struct sockaddr_in * ser_addr, int * server_socket_fd, int PORT, const char *Myip);
int MessageProcessing(char *message, int size, char Type, struct loTMetadata *SloT, struct loTMetadata *DloT = NULL);
int SendMessage(loTMetadata* DloT);

static std::map<char, int> TypeLength = {{'0', 24}, {'1', 17}, {'2', 16}};

#endif