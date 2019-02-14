#include "../include/apue.h"
#include <fcntl.h>

#define PATHNAME "./mkfifof.txt"

int main(void){
    pid_t pid;
    int fd = -1;
    char buf[BUFSIZ] = "";

    // 创建一个命名管道，通过ls -l查看这个管道的属性
    if(mkfifo(PATHNAME,0664)<0){
        err_sys("mkfifo");
    }

    fflush(NULL); // 刷新缓冲区
    pid = fork();

    if(pid<0)
        err_sys("fork()");

    if(!pid){
        pid = fork(); // 继续fork 三个进程了
        if(pid<0)err_sys("fork()2");
        if(!pid) exit(0); // 爸爸走了
       // child2
        fd = open(PATHNAME,O_RDWR);
        if(fd<0) err_sys("open()");
        // 阻塞，等待条件满足
        read(fd,buf,BUFSIZ);
        printf("%s\n",buf);
        write(fd," World!",8);
        close(fd);
        exit(0);
    }else{
        fd = open(PATHNAME,O_RDWR);
        if(fd < 0) err_sys("open()");
        // 写
        write(fd,"hello",6);
        sleep(1); // 要是不休眠就没有给另一个进程机会写，最后自娱自乐，第二个进程也打不开文件
        read(fd,buf,BUFSIZ);
        close(fd);
        puts(buf);
        // 这个进程最后退出，所以把管道文件删除，不然下次在创建的时候会报文件已存在的错误
        remove(PATHNAME);
        exit(0);
    }
    return 0;
}