#include "../include/apue.h"
#include <pthread.h>
#include <string.h>

#define THRNUM 4
static pthread_mutex_t mut[THRNUM]; // 定义四个互斥量

static int next(int a){
    if(a+1 == THRNUM) // 0，1，2，3
        return 0;
    return a+1;
}

static void *thr_func(void *p){
    int n = (int)p;
    int ch = n+'a';
    while(1){
        pthread_mutex_lock(mut+n);// 锁住自己的互斥量
        write(1,&ch,1);
        pthread_mutex_unlock(mut+next(n));// 🔓解锁下一线程对应的互斥量
    }
    pthread_exit(NULL);
}

int main(){
    int i,err;
    pthread_t tid[THRNUM];
    for(i = 0;i<THRNUM;i++){
        pthread_mutex_init(mut+i,NULL);
        pthread_mutex_lock(mut+i);
        err = pthread_create(tid+i,NULL,thr_func,(void*)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);
        }
    }
    pthread_mutex_unlock(mut+1); // 解锁其中一个
    alarm(5);
    for(i = 0;i<THRNUM;i++){
        pthread_join(tid[i],NULL);
    }

    exit(0);
}