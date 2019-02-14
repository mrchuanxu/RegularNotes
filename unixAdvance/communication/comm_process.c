#include "../include/apue.h"

#define BUFSIZE 1024

int main(){
    int pd[2];
    int ipd[2];
    char buf[BUFSIZE];
    char dbuf[BUFSIZE];
    pid_t pid;
    int len;
    // 创建匿名管道
    if(pipe(pd)<0)
        err_sys("pipe()");
    if(pipe(ipd)<0) err_sys("pipe2");
    pid = fork();
    if(pid == 0){ // 子进程 读取管道数据
        // 关闭写端
       // close(pd[1]);
        // 从管道中读取数据，如果子进程比父进程先被调度会阻塞等待数据写入
        //len = read(pd[0],buf,BUFSIZE);
       // puts(buf);
        /***
         * 管道fork之前创建
         * 父子进程都有一份
         * 所有退出之前要确保管道两端都关闭
         * ***/
        close(pd[0]);
        write(pd[1],"hello,child!",15);
        // sleep(10)；
        //sleep(10);
        len = read(ipd[0],dbuf,BUFSIZE);
        puts(dbuf);
        close(pd[1]);
        close(ipd[0]);
        exit(0);
    }else{ // 父进程 向管道写入数据
        // 关闭读端
        //close(pd[0]);
        // 写端
       // write(pd[1],"Hello,world!",15);
        close(pd[1]);
        len = read(pd[0],buf,BUFSIZE);
        puts(buf);
        // 关闭读端
        // sleep(5);
        write(ipd[1],"hello parent!",BUFSIZE);
        close(pd[0]);
        close(ipd[1]);
        wait(NULL);
        exit(0);
    }
}