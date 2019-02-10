#include "../include/apue.h"
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;
// 初始化互斥量的条件

void *thr_fn(void *arg){
    int err,sig;
    for(;;){
        err = sigwait(&mask,&sig); // 等待一个或多个信号的到来 并初始化sig
        if(err!=0)
            err_exit(err,"sigwait failed");
            switch (sig)// 判断信号的类型
            {
                case SIGINT:
                    printf("\ninterrupt\n");
                    /* code */
                    break;
                case SIGQUIT:
                    pthread_mutex_lock(&lock);
                    quitflag = 1;
                    pthread_mutex_unlock(&lock);
                    pthread_cond_signal(&waitloc);
                    // 发布得到信号的条件，通知其他线程
                    return (0);
                default:
                    printf("unexpected signal %d\n",sig);
                    exit(1);
            }
    }
}

int main(void){
    int err;
    sigset_t oldmask;
    pthread_t tid;

    sigemptyset(&mask); // 添加信号集
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);

    if((err = pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0) // 修改mask
        err_exit(err,"SIG_BLOCK error");
    
    err = pthread_create(&tid,NULL,thr_fn,0);

    if(err!=0)
        err_exit(err,"can't create thread");

    pthread_mutex_lock(&lock);
    while(quitflag == 0)
        pthread_cond_wait(&waitloc,&lock); // 线程等待条件变量
    pthread_mutex_unlock(&lock);

    quitflag = 0;

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0) // sigpromask 重置mask位图
        err_sys("SIG_SETMASK error");
    exit(0);
}