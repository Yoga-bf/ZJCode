#ifndef COMTHREAD_
#define COMTHREAD_

void* Recv_loT_Signup(int server_socket_fd);
void* Com_with_loT(loTMetadata* myloT);
void* Pcap_Receive();



#endif