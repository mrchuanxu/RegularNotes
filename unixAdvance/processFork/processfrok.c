#include "../include/apue.h"
/***
 * 子进程对变量所做的改变并不影响父进程中该变量
 * 0 调度进程 交换进程 新进程创建ID不可能是0 所以可以返回 0
 * 1 init进程
 * 2 页守护进程
 * pid_t fork(void); // fork新进程 子进程返回 0，父进程返回子进程🆔
 * 子进程是父进程的副本，子进程获得父进程数据空间、堆和栈的副本。子进程所拥有的副本！父进程和子进程并不共享这些存储空间部分。
 * 父进程和子进程共享正文段
 * fork后跟着exec
 * ***/
int globvar = 6;
char buf[] = "a write to stdout;\n"; // buf改变变量
int subProcess(int a){
    a+=a;
    return a;
}
int main(void){
    int var;
    pid_t pid; // 进程pid

    var = 88;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1) // 输出
        err_sys("write error!");
    printf("before fork\n"); // before fork
    //printf("pid=%ld,glob=%d,vr=%d\n",(long)geteuid(),globvar,var); 
    pid = fork(); // fork之后，将会有两个进程在跑，一个是父进程在跑，一个是子进程在跑 fork之后就是两个程序在跑了！
    fflush(NULL);
    if(pid<0) // 0 调度进程 交换进程
        err_sys("fork error");
    else if(pid==0){
        printf("i am subProcess and i will add globvar 1\n");
        //printf("pid=%ld,glob=%d,vr=%d\n",(long)getppid(),globvar,var);
        printf("a=%d\n",subProcess(10));
        globvar++;
        var++;
    }else{
        sleep(3);
        //printf("a=%d\n",subProcess(420)); // 可以等待其他请求
        //printf("i am Process and i sleep\n");
    }
    int i = printf("pid=%ld,glob=%d,vr=%d\n",(long)getpid(),globvar,var); 
    printf("i=%d\n",i);
    //printf("pid=%ld,glob=%d,vr=%d\n",(long)getppid(),globvar,var); 
    exit(0);
}
