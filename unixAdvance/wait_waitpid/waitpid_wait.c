#include "../include/apue.h"
#include <sys/wait.h>

int main(void){
    pid_t pid;
     if((pid=fork())<0){
         err_sys("fork error");
     }else if(pid==0){ // 子进程
         if((pid=fork())<0) // 子进程的子进程
             err_sys("fork error");
         else if(pid>0)
             exit(0);
        //sleep(5);
        printf("second child,parent pid=%ld\n",(long)getppid());
        exit(0);
     }
     if(waitpid(pid,NULL,0)!=pid)
         err_sys("waitpid error");
    printf("i am parent pid=%ld\n",(long)getpid());
    exit(0);
}