#include "../include/apue.h"
#include <fcntl.h>
#include <sys/wait.h>
#define BUFSIZE 1024
int main(){
    int fd;
    char buf[BUFSIZE];
    int size;
    if((fd = open("./advance.txt",O_RDONLY|O_NONBLOCK))<0){
        err_sys("wrong open");
    }
    while(1){
        if((size = read(fd,buf,BUFSIZE))<0){
            if(EAGAIN = errno){
                continue;
            }
            err_sys("read()");
            exit(1);
        }
// dosth
    }
}