#include "../include/apue.h"
#include <stdio.h>
#include <unistd.h>

int main(void){
    pid_t pid;
    int i = 0;
    for(;i<10;i++){
        fflush(NULL);
        if((pid = fork())<0){
            err_sys("fork error");
            exit(1);
        }else if(0==pid){
           // sleep(100);
            printf("pid=%d\n",getpid());
            exit(0);
        }
    }
    for(i=0;i<10;i++){
        wait(NULL);
    }
    exit(0);
}