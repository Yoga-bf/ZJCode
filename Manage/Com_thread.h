#ifndef COMTHREAD_
#define COMTHREAD_

void* Recv_loT_Signup(int server_socket_fd, loTDatabase* AllloT);
void* Com_with_loT(loTMetadata* myloT, loTDatabase* AllloT);




#endif