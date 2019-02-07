#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s){
    write(1,"!",1);
}

int main(){
    sigset_t set,oset,saveset;
    int i,j;

    signal(SIGINT,int_handler); // 这里要是改为实时信号，那么收到多少个信号就打印多少行星号
    printf("signal_print\n");
    sigemptyset(&set); // 置空信号
    sigaddset(&set,SIGINT); // 赋值信号

    sigprocmask(SIG_UNBLOCK,&set,&saveset); // 解除屏蔽 mask设为1 这里保证mask值一定为1

    sigprocmask(SIG_BLOCK,&set,&oset); // 屏蔽信号 mask设为0

    for(j = 0;j<10000;j++){
        for(i = 0;i<5;i++){
            write(1,"*",1);
            sleep(1); // 这里实现每一秒打印一次
        }
        write(1,"\n",1);
        sigsuspend(&oset); //   等待被信号打断，再重新屏蔽信号 这里的mask置为1
    }

    sigprocmask(SIG_SETMASK,&saveset,NULL); // mask恢复0，其他信号恢复为1
    exit(0);
}