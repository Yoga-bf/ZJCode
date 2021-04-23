#ifndef Net_
#define Net_

const static char SignUp = '0';
const static char SignDown = '1';
const static char Com = '2';

const int N = 1024;
void SocketMake(struct sockaddr_in * ser_addr, int * server_socket_fd, int PORT, const char *Myip);
int MessageProcessing(char *message, int size, char Type);

#endif