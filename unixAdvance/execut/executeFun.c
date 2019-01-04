#include "../include/apue.h"
#include <sys/wait.h>

char *env_init[] = {"User = unknown","PATH=/tmp",NULL};

int main(void){
    pid_t pid;
    fflush(NULL);
    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        if(execle("/Users/transcheung/Documents/RegularNotes/unixAdvance/testinterp","echoall","myargl","MY ARG2",(char *)0,env_init)<0)
            err_sys("execle error");
        exit(0);
    }
    if(waitpid(pid,NULL,0)<0)
        err_sys("wait error");
    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        if(execlp("echoall","echoall","only 1 arg",(char*)0)<0)
            err_sys("execlp error");
    }
    printf("i am father");
    exit(0);
}