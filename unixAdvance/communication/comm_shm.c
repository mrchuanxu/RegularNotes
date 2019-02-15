#include "../include/apue.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define MEMSIZE 1024

int main(){
    char *str;
    pid_t pid;
    int shmid;
    // 有亲缘关系的进程key参数可以使用IPC_PRIVATE宏，并且创建共享内存
    // shmflg参数不需要使用IPC_CREAT宏
    shmid = shmget(IPC_PRIVATE,MEMSIZE,0600);
    if(shmid < 0) err_sys("shmget()");
    if((pid = fork())<0) err_sys("fork()");
    if(pid==0){// 子进程
        // 关联共享内存
        str = shmat(shmid,NULL,0);
        if(str == (void*)-1) err_sys("shmat()");
        // 向共享内存写入数据
        strcpy(str,"hello!");
        // 分离共享内存
        shmdt(str);
        // 无需释放
        exit(0);
    }else{
        // 等待子进程结束后再运行，需要读取子进程写入的共享内存的数据
        wait(NULL);
        // 关联共享内存
        str = shmat(shmid,NULL,0);
        if(str == (void *)-1) err_sys("shmat()");
        // 打印读出来的数据
        puts(str);
        // 分离共享内存
        shmdt(str);
        // 释放共享内存
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
    }
    exit(0);

}