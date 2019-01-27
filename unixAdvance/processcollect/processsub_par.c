#include "../include/apue.h"

/***
 * 父子进程各有各事情
 * 每个进程在执行完它的一套初始化操作后要通知对方
 * 并且在继续执行之前，要等待另一方完成其初始化操作
 * ***/
/***
 * 输出字符串，一个由子进程输出，另一个由父进程输出
 * 输出依赖于内核，使两个进程运行的顺醋以及每个进程运行的时间长度
 * ***/

static void charatatime(char *);// static 让其作为程序的唯一函数
int main(void){
    pid_t pid;

    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        charatatime("out put by child\n");
    }else{
        charatatime("out put by paren\n");
    }
    exit(0);
}

static void charatatime(char *str){
    char *ptr;
    int c;
    setbuf(stdout,NULL);
    for(ptr = str;(c=*ptr++)!=0;){
        putc(c,stdout);
    }
}