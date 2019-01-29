#include "../include/apue.h"
/***
 * 创建子进程date，参数是+%s
 * 相当于在shell中执行date+%s命令
 * ***/
int main(){
    pid_t pid;

    puts("Begin!");

    fflush(NULL);

    pid = fork();

    if(pid<0){
        err_sys("fork error");
        exit(1);
    }
    if(pid == 0){
        execl("/bin/sh","sh","-c","date +%s",NULL);
        err_sys("execl()");
        exit(1);
    }
    wait(NULL);
    puts("END");
    exit(0);
}