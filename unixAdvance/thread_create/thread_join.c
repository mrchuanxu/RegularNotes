#include "../include/apue.h"
#include <pthread.h>

void cleanup(void *arg){
    printf("clean up:%s\n",(char *)arg);
}

void* thr_fn1(void *arg){
    printf("thread 1 returning\n");
    pthread_cleanup_push(cleanup,"thread 1 first handler");
    pthread_cleanup_push(cleanup,"thread 1 second handler");
    printf("thread 1 push complete");
    if(arg)
        return((void*)1);
    pthread_cleanup_pop(1);// 成对出现
    pthread_cleanup_pop(1);
    return ((void*)1);
}

void* thr_fn2(void *arg){
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup,"thread 2 first handler");
    pthread_cleanup_push(cleanup,"thread 2 second handler")
    printf("thread 2 push complete\n");
    if(arg)
        pthread_exit((void *)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void *)2);
}

int main(void){
    int err;
    pthread_t tid1,tid2; // 创建两个线程
    void *tret;

    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 1");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 2");
    err = pthread_join(tid1,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 1");
    printf("thread 1 exit code %ld\n",(long)tret);
    // 线程结束返回码
    err = pthread_join(tid2,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 2");
    printf("thread 2 exit code %ld\n",(long)tret);
    exit(0);
}