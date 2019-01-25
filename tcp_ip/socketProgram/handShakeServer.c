#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc/malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>

int main(){
    int sockSrv = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addrSrv;
    addrSrv.sin_family = AF_INET;// ip
    addrSrv.sin_addr.s_addr = INADDR_ANY;//协议
    addrSrv.sin_port = htons(8085);//端口
    bind(sockSrv,(const struct sockaddr*)&addrSrv,sizeof(struct sockaddr_in)); // 绑定监听的端口
    listen(sockSrv,5); // 服务端开始监听端口
    struct sockaddr_in addrClient;
    int len = sizeof(struct sockaddr_in);
    int sockCOnn = accept(sockSrv,(struct sockaddr*)&addrClient,(socklen_t*)&len);
    unsigned int total = 0;
    char szRecvBuf[128] = {0};
    int iRet = recv(sockCOnn,szRecvBuf,sizeof(szRecvBuf)-1,0);
    printf("iRet is %u\n",iRet);

    getchar();
    close(sockCOnn);
    close(sockSrv);
    return 0;
}