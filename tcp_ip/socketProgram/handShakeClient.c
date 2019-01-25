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

// 客户端会比较简单一点 只有connect
int main(){
    int sockClient = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addrSrv;
    addrSrv.sin_addr.s_addr = inet_addr("10.7.1.104");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8085);
    connect(sockClient,(const struct sockaddr*)&addrSrv,sizeof(struct sockaddr_in));
    char szSendBuf[] = "fuck";
    int iRet = send(sockClient,szSendBuf,strlen(szSendBuf),0);
    printf("send size is %d,iRet is %d\n",strlen(szSendBuf),iRet);
    getchar();
    close(sockClient);
    return 0;
}