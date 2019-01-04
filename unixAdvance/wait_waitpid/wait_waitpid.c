#include "../include/apue.h"
#include <sys/wait.h>

void pre_exit(int status){
    if(WIFEXITED(status))
        printf("normal termination, exit status=%d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination,signal number=%d%s\n",WTERMSIG(status),
        #ifdef WCOREDUMP
                WCOREDUMP(status)?"(core file generated":"");
        #else
        "");
        #endif
    else if(WIFSTOPPED(status))
        printf("child stopped,signal number=%d\n",WSTOPSIG(status));
}

int main(void){
    pid_t pid;
    int status;

    if((pid=fork())<0)
        err_sys("fork error");
    else if(pid==0) // child
        exit(7);

    if(wait(&status)!=pid) // wait child
        err_sys("wait error");
    pre_exit(status); // print status

    if((pid=fork())<0)
        err_sys("fork error"); 
    else if(pid==0) // child
        abort(); // generates SIGABRT

    if(wait(&status)!=pid)
        err_sys("wait error");
    pre_exit(status);

    if((pid=fork())<0)
        err_sys("fork error");
    else if(pid==0) // child
        status/=0; // divide by 0 generate sinfre
    
    if(wait(&status)!=pid) // wait child 
        err_sys("wait error");
    pre_exit(status); // print status

    exit(0);
}