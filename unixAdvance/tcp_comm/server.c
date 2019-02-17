#include "../include/apue.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "proto.h"

#define IPSTRSIZE 40

static void server_job(int sd){
    char buf[BUFSIZ];
    int len;

    len = sprintf(buf,FMT_STAMP,(long long)time(NULL));

    if(send(sd,buf,len,0)<0) err_sys("send()");
    return;
} 

int main(){
    int sd,newsd;
    struct sockaddr_in laddr,raddr;
    socklen_t raddr_len;
    char ipstr[IPSTRSIZE];
    // 选择TCP协议
    sd = socket(AF_INET,SOCK_STREAM,0);
    if(sd<0) err_sys("socket()");
    // SO_REUSEADDR用来设置端口被释放后可立即被重新使用
    int val = 1;
    if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))<0) err_sys("setsockopt()");

    laddr.sin_family = AF_INET;
    // 指定服务端使用的端口号
    laddr.sin_port = htons(atoi(SERVERPORT));
    inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr.s_addr);

    // 绑定端口
    if(bind(sd,(void*)&laddr,sizeof(laddr))<0) err_sys("bind()");
    
    // 开始监听端口

    if(listen(sd,200)<0) err_sys("listen()");
    raddr_len = sizeof(raddr);

    while(1){
        // 阻塞等待新消息传入
        newsd = accept(sd,(void*)&raddr,&raddr_len);
        // 这里就是怕假错，而且文件描述符不能用开始哪个！
        if(newsd<0){
            if(errno == EINTR||errno == EAGAIN)
                continue;
            err_sys("newsd()");
        }
        inet_ntop(AF_INET,&raddr.sin_addr,ipstr,IPSTRSIZE);
        printf("Client:%s:%d\n",ipstr,ntohs(raddr.sin_port));
        server_job(newsd);
        close(newsd);
    }
    close(sd);
    exit(0);
}