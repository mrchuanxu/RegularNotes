#include "../include/apue.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "proto.h"

#define IPSTRSIZE 64

int main(){
    int sd; // socket的文件描述符
    struct sockaddr_in laddr,raddr;
    socklen_t raddr_len;

    struct msg_st rbuf;
    char ipstr[IPSTRSIZE];

    sd = socket(AF_INET,SOCK_DGRAM,0); // UDP
    if(sd < 0) err_sys("socket()");

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr.s_addr);

    if(bind(sd,(void*)&laddr,sizeof(laddr))<0) err_sys("bind()");
    raddr_len = sizeof(raddr);

    while(1){
        if(recvfrom(sd,&rbuf,sizeof(rbuf),0,(void*)&raddr,&raddr_len)<0) err_sys("recvfrom()");

        inet_ntop(AF_INET,&raddr.sin_addr,ipstr,IPSTRSIZE);
        printf("--MESSAGE FROM:%s:%d--\n",ipstr,ntohs(raddr.sin_port));
        printf("Name = %s\n",rbuf.name);
        printf("Math = %d\n",ntohl(rbuf.math));
        printf("Chinese = %d\n",ntohl(rbuf.chinese));
    }
    close(sd);
    exit(0);
}