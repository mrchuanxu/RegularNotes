#include "../include/apue.h"
#include <sys/wait.h>
#include <sys/types.h>

// void pr_exit(int status){
//     if(WIFEXITED(status))
//         printf("nomal termination,exit status = %d\n",WEXITSTATUS(status));
//     else if(WIFSIGNALED(status))
//         printf("abnormal termination,signal number = %d%s\n");
//     #ifdef WCOREDUMP
//         WCOREDUMP(status)?"(core file generated":"");
//     #else
//         "");
//     #endif
//         else if(WIFSTOPPED(status))
//             printf("child stopped,signal number = %d\n",WSTOPSIG(status));
// }
int main(){
    pid_t pid; // 子进程id获取
    int i;
    for(i=0;i<10;i++){
        fflush(NULL);
        if((pid=fork())<0){
            err_sys("fork error");
            exit(0);
        }else if(0==pid){
            printf("get child id=%d\n",getpid());
            sleep(2);
            exit(0);
        }
    }
    for(i=0;i<10;i++){
       pid =  wait(NULL); // 父进程为所有的子进程收尸
       printf("collect id=%d\n",pid);
    }
    return 0;
}