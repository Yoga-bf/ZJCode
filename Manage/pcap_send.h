#ifndef PCAP_SEND_
#define PCAP_SEND_
#define _PCAP_SEND_H_
#define _SEND_UDP_H_
#define _GET_PACK_CONTENT_H_
#define _PACK_BLD_H_
#define _PCAP_SEND_H_
#ifdef __cplusplus
extern "C" {
#endif

void pcap_send(char *buf, char *dmac, char *dip, int num, int buff_len);
int pcap_snd_udp_pack(char *udp_pack, char *UDP_PACK, char *dev_name ,int num, int lot_len);
int bld_udp_pack(char *pack, char *UDP_PACK, int lot_len);
int pcap_snd_pack(char *pkt, char *dev_name , int num);
int pcap_receive();

#define MAX 1024
#define DEV_NAME "ens33"
#define DEFAULT_MAC "111111"
#define DEFAULT_IP "10.0.0.1"

//#define DST_IP "6.6.6.6"
//#define SRC_IP "192.168.4.167"
extern char DST_IP[];
extern char SRC_IP[];

#define COMPILE_IP "dst host 192.168.4.167"
#define COMPILE_PORT "dst port 80"


#ifdef __cplusplus
}
#endif
#endif