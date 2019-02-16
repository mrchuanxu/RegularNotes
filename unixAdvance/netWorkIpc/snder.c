#include "../include/apue.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "proto.h"

int main(int argc,char **argv){
    int sd;
    struct msg_st sbuf;
    struct sockaddr_in raddr;
    
    if(argc<2) err_sys("Usage ...\n");

    sd = socket(AF_INET,SOCK_DGRAM,0);

    if(sd<0) err_sys("socket()");

    // bind(); 主动端可省略绑定端口的步骤

    memset(&sbuf,'\0',sizeof(sbuf));
    strcpy(sbuf.name,"Trans");
    sbuf.math = htonl(rand()%100);
    sbuf.chinese = htonl(rand()%100);

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,argv[1],&raddr.sin_addr);

    if(sendto(sd,&sbuf,sizeof(sbuf),0,(void*)&raddr,sizeof(raddr))<0) err_sys("sendto");

    puts("ok!");

    close(sd);
    exit(0);
}