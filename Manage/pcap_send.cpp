#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <pcap/pcap.h>
#include <net/if.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "pcap_send.h"

int port = 8000;
int pack_len = 100;
static char errbuf[PCAP_ERRBUF_SIZE];
char    dstmac[6]={248,15,65,246,104,77};
char    srcmac[6]={248,15,65,246,104,78};
char    dstip[16];
char    srcip[16];
int pack_real_len = 0;

void pcap_callback(unsigned char * arg, const struct pcap_pkthdr *packet_header, const unsigned char *packet_content);

static void net_dev_close(pcap_t *dev)
{
	printf("Close Device\n");
	if(dev){
	    pcap_close(dev);
	}
}

void pcap_send(char *buff, char *dmac, char *dip, int num, int buff_len){
    char dev_name[10] = {0};
    int len;
    int ret;
    int i,j;
    char buf[MAX];
    
    sprintf(dev_name, DEV_NAME);
    memset(dstip, 0, sizeof(dstip));
    memset(srcip, 0, sizeof(srcip));
    strcat(srcip, SRC_IP);
    
    if (dmac == NULL) {
    } else {
        strcpy(dstmac, dmac);
    }

    if (dip == NULL) {
        strcpy(dstip, DST_IP);
    } else {
        strcpy(dstip, dip);
    }

    pcap_snd_udp_pack(buf, buff, dev_name, num, buff_len);

}

int pcap_snd_udp_pack(char *udp_pack, char *UDP_PACK, char *dev_name ,int num, int lot_len){
    int ret;
    ret = bld_udp_pack(udp_pack, UDP_PACK, lot_len);
    if((ret = pcap_snd_pack(udp_pack, dev_name , num)) == -1){
        perror("pcap_snd_udp_pack()...pcap_snd_pack fail.\n");
        return -1;
    }
    return 0;
}

int bld_udp_pack(char *pack, char *UDP_PACK, int lot_len){
    struct ethhdr *peth;
    struct iphdr *pip;
    struct udphdr *udp;
    int hdr_size;
    char buf[pack_len];
    int i;
    
    bzero(pack, sizeof(pack));
    
    peth = (struct ethhdr *)pack;
    pip = (struct iphdr *)(pack + sizeof(struct ethhdr));
    udp = (struct udphdr *)(pack + sizeof(struct ethhdr) + sizeof(struct iphdr));
    hdr_size = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
    printf("the long of the udp is %d\n", hdr_size);
    
    for(i = 0 ; i < 6 ; i++)
	{
		peth->h_dest[i] = dstmac[i];
		peth->h_source[i] = srcmac[i];
	}
	peth->h_proto = htons(ETH_P_IP);
	
    pip->ihl = 5;
    pip->version = 4;
    pip->tos = 0;
    pip->id = 0;
    pip->frag_off = 0;
    pip->ttl = 64;
    pip->protocol = IPPROTO_UDP;          //ip->protocol = IPPROTO_UDP
    pip->saddr = inet_addr(srcip);
    pip->daddr = inet_addr(dstip);
    pip->check = 0;
    
    udp->source= htons(port);
    udp->dest  = htons(port);
    udp->check = 0;
    udp->len   = sizeof(struct udphdr);
    
    for(i = 0 ; (i < pack_len) && (i < lot_len) ; i++){
        pack[hdr_size+i] = UDP_PACK[i];
    }
    
    pack_real_len = lot_len + hdr_size;

    return hdr_size+strlen(UDP_PACK);
}

int pcap_snd_pack(char *pkt, char *dev_name , int num){
    
    int i ;
    pcap_t *fp = NULL ;
    
    fp=pcap_open_live(dev_name, 8000, 1, 500, errbuf);
    if(fp == NULL){
        perror("error in creating dev fp\n");
        return -1 ;
    }

    for(i = 0 ; i < num ; i++){
        printf("begin to pcap_sendpacket----");
        pcap_sendpacket(fp, (const u_char *)pkt, pack_real_len);
        printf("success\n") ;
        sleep(1) ;
    }
    net_dev_close(fp) ;
    
    return 0 ;
}


int pcap_receive()
{

    char *dev,errbuf[1024];
    dev = (char*)malloc(8);
    char compile[30];
    memset(dev,0,sizeof(dev));
    strcpy(dev,DEV_NAME);

    if(dev==NULL){
        printf("device is null\n");
        return 0;
    }

    pcap_t *pcap_handle=pcap_open_live(dev,65535,1,0,errbuf);
    if(pcap_handle==NULL){
        printf("%s\n",errbuf);
        return 0;
    }

    memset(compile,0,sizeof(compile));
    strcpy(compile,COMPILE_PORT);
    struct bpf_program filter;
    if(pcap_compile(pcap_handle,&filter,compile,1,0)<0){
        printf("error\n");
        return 0;
    }
    if(pcap_setfilter(pcap_handle,&filter)<0){
        printf("error\n");
        return 0;
    }

    while(1){
        if(pcap_loop(pcap_handle,-1,pcap_callback,NULL)<0){
        printf("error in receive packet\n");
        }
    }
    
}

void pcap_callback(unsigned char * arg, const struct pcap_pkthdr *packet_header, const unsigned char *packet_content)
{

    printf("Packet length : %d\n", packet_header->len);
    printf("Number of bytes : %d\n", packet_header->caplen);

    int i;
    for(i = 0; i < packet_header->caplen; i++){
        printf(" %02x",packet_content[i]);
        if((i+1)%16==0){
            printf("\n");
        }
    }

    struct ethhdr *peth;
    struct iphdr *pip;
    struct udphdr *udp;
    char *lot_information;
    
    u_int eth_len = sizeof(struct ethhdr);
    u_int ip_len = sizeof(struct iphdr);
    u_int udp_len = sizeof(struct udphdr);
    u_int all_len = eth_len + ip_len + udp_len;

    peth = (struct ethhdr *)packet_content;
    pip = (struct iphdr *)(packet_content + eth_len);
    udp = (struct udphdr *)(packet_content + eth_len + ip_len);
    lot_information = (char *)(packet_content + all_len);

    if( lot_information[0] == '0' || lot_information[0] == '1' || lot_information[0] == '2' ){
        printf("success receive!\n");
    }

}