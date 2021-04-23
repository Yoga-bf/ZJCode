#ifndef Net_
#define Net_

#include <map>


const static char SignUp = '0';
const static char SignDown = '1';
const static char Com = '2';

const int N = 1024;
void SocketMake(struct sockaddr_in * ser_addr, int * server_socket_fd, int PORT, const char *Myip);
int MessageProcessing(char *message, int size, char Type, char *SID, char *DID);

static std::map<char, int> length_type = {{'0', 24}, {'1', 17}, {'2', 16}};

#endif