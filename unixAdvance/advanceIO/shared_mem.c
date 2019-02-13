#include "../include/apue.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PROCNUM 20
#define FNAME "./advance.txt"
#define BUFSIZE 1024

static void func_add(){
    FILE *fp;
    int fd;
    char buf[BUFSIZE];

    fp = fopen(FNAME,"r+");
    // 标准输出
    if(fp == NULL){
        err_sys("fopen()");
    }

    fd = fileno(fp);

    if(fd<0)
        err_sys("fd error");
    
    // 使用之前先锁定
    lockf(fd,F_LOCK,0);

    fgets(buf,BUFSIZE,fp);
    // 把文件位置指针定位到文件首
    rewind(fp);
    sleep(1);
    fprintf(fp,"%d\n",atoi(buf)+1);
    // 输出到文件中
    // atoi转ascii 字符串到数字
    fflush(fp);

    // 使用之后释放锁
    lockf(fd,F_ULOCK,0);
    return;
}
// 如果加不上锁就等，等别人释放锁再加，如果加上了锁就读文件的值再+1

int main(void){
    int i;
    pid_t pid;

    for(i = 0;i<PROCNUM;i++){
        pid = fork();
        if(pid<0){
            err_sys("fork()");
        }
        if(pid == 0){
            func_add();
            exit(0);
        }
    }

    for(i = 0;i<PROCNUM;i++)
        wait(NULL);

    exit(0);
}
