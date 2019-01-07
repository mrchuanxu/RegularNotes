/***
 * 文件共享
 * unix系统支持不同进程间共享打开文件
 * 在介绍dup函数之前，先要说明这种共享
 * 
 * 先介绍一下内核用于所有I/O的数据结构
 * 3种数据结构
 * 一、 每个进程在进程表中都有一个记录项，记录项中包含一张打开文件描述符表
 * 可将其视为一个矢量，每个描述符占用一项
 * a. 文件描述符标志
 * b. 指向一个文件表项的指针
 * 二、内核为所有打开文件维持一张文件表
 * a. 文件状态标志
 * b. 当前文件偏移量
 * c. 指向该文件v节点表项的指针
 * 三、每个打开文件（或设备）都有一个v结点v-node结构 Linux没有v节点，而是使用了通用i节点结构
 * v节点包含了文件类型和对此文件进行各种操作函数的指针
 * 文件描述符标志和文件状态标志有区别
 * 文件描述符：用于一个进程的一个描述符
 * 文件状态标志 应用于指向该给定文件表项的任何进程中的所有描述符
 * 追加一个文件
 * 原子操作 指的是由多步组成的一个操作 如果该操作原子地执行 要么执行所有步骤
 * 函数dup和dup2 可用来复制一个现有的文件描述符
 * 两函数的返回值，若成功，返回新的文件描述符，若出错，返回-1
 * 
 * ***/

#include <unistd.h>
#include "../include/apue.h"
#include <fcntl.h>

char buf[] = "i am your father";
char buf1[] = "who the hell are you?";

int main(){
    int fd,fdup;
    int n;
    if((fd = open("./shareFile.hole",O_WRONLY))<0){
        if(errno == ENOENT){
            if((fd=creat("./shareFile.hole",FILE_MODE))<0)
                err_sys("create error");
        }else{
            err_sys("open error");
        }
    }
    fdup = dup(fd); // fdup指定新描述符的值
    int pid;
    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid==0){ // 这里创建了一个子进程，写入一串字符串
        if((n=write(fdup,buf1,21))!=21)
           err_sys("write error");
        exit(0);
    }
    printf("fdup:%d,fd:%d\n",fdup,fd);
    if((n=write(fd,buf,20))!=20) // 这里反而写不进去？
        err_sys("write error");
    exit(0);
}