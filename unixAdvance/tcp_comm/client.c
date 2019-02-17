#include "../include/apue.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "proto.h"

int main(int argc,char **argv){
    int sd;
    FILE *fp;
    struct sockaddr_in raddr;
    long long stamp;
    if(argc<2) err_sys("Usage...\n");

    // TCP协议
    sd = socket(AF_INET,SOCK_STREAM,0);
    if(sd < 0) err_sys("socket()");

    raddr.sin_family = AF_INET;
    // 指定端口号
    raddr.sin_port = htons(atoi(SERVERPORT));
    // 指定ip
    inet_pton(AF_INET,argv[1],&raddr.sin_addr);
    // 发起请求
    if(connect(sd,(void*)&raddr,sizeof(raddr))<0) err_sys("connect()");

    fp = fdopen(sd,"r+");
    if(fp == NULL) err_sys("fdopen()");

    // 读取服务端响应
    if(fscanf(fp,FMT_STAMP,&stamp)<1) fprintf(stderr,"fscanf() failed\n");
    else
    {
        printf("stamp = %lld\n",stamp);
    }
    fclose(fp);
    exit(0);
}