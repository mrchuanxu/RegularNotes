/***
 * 关于僵死进程，如果一个进程fork一个子进程，但不要它等待子进程终止
 * 也不希望子进程处于僵死状态直到父进程终止
 * fork两次？
 * 我们来看看如何fork两次，也就是说，原来的父进程成为了爷爷
 * 原来的子进程有了个儿子
 * ***/
#include "../include/apue.h"
#include <sys/wait.h>

int main(void){
    pid_t pid;

    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        printf("first child,child pid = %ld\n",(long)getpid());
        sleep(2);
        if((pid=fork())<0) // 子进程又fork一次
            err_sys("fork error");
        else if(pid>0){ // 可以看出pid是两个值，一个是父进程ID
            printf(">0 pid = %ld\n",(long)getpid());
            // exit(0);
        }
        else if(pid == 0){ // 一个是子进程环境的执行
            printf("=0 pid = %ld\n",(long)getpid()); // 子进程的ID
            exit(0);
        }
        // 父进程退出了，init回收孤儿子进程
        printf("second child,parent pid = %ld\n",(long)getpid());
        sleep(4);
        exit(0);
    }
    printf("parent pid = %ld\n",(long)getpid());
    printf("pid = %d\n",pid);
    if(waitpid(pid,NULL,0)!=pid) // 非阻塞的方式回收资源子进程资源
        err_sys("waitpid error");
    sleep(10);
    exit(0);
}