#include "../include/apue.h"
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define PROCNUM 20
#define FNAME "./test.txt"
#define BUFSIZE 1024

// 多个函数都要使用这个信号量ID，所以定义为全局变量
static int semid;

// P操作
static void P(void){
    struct sembuf op;
    op.sem_num = 0; // 只有一个资源所以数组下标是0
    op.sem_op = -1; // 取一个资源就减1
    op.sem_flg = 0; // 没有特殊要求
    while(semop(semid,&op,1)<0){
        if(errno != EINTR && errno!=EAGAIN) err_sys("semop()");
    }
}
// V操作
static void V(void){
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    while(semop(semid,&op,1)<0){
        if(errno != EINTR && errno != EAGAIN) err_sys("semop()");
    }
}

static void func_add(){
    FILE *fp;
    char buf[BUFSIZE];
    fp = fopen(FNAME,"r+");
    if(fp == NULL) err_sys("fopen()");
    // 先取得信号量再操作文件，取不到就阻塞等待，避免发生竞争
    P();
    fgets(buf,BUFSIZE,fp); // 获取一行字符串
    rewind(fp); // 从头指针开始
    sleep(1); // 放大竞争
    fprintf(fp,"%d\n",atoi(buf)+1);
    fflush(fp);
    // 操作结束，归还信号量，让其他进程可以取得信号量
    V();
    fclose(fp);
    return;
}

int main(){
    int i;
    pid_t pid;

    // 在具有亲缘关系的进程之间使用，所以设置为IPC_PRIVATE
    // 另外想要实现互斥量的效果，所以信号量数量设置为1个即可
    semid = semget(IPC_PRIVATE,1,0600);
    if(semid<0) err_sys("semget()");
    // 将union semun.val的值设置为1
    if(semctl(semid,0,SETVAL,1)<0) err_sys("semctl()");

    // 创建20个子进程
    for(i = 0;i<PROCNUM;i++){
        pid = fork();
        if(pid<0) err_sys("fork()");
        if(pid == 0){
            func_add();
            exit(0);
        }
    }

    for(i = 0;i<PROCNUM;i++) wait(NULL);

    // 销毁信号量
    semctl(semid,0,IPC_RMID);
    exit(0);
}