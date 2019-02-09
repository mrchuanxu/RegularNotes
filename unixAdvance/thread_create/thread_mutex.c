#include "../include/apue.h"
#include <pthread.h>
#include <string.h>

#define THRNUM 4
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;
static int num = 0;
static int next(int a){
    if(a+1 == THRNUM) // 0，1，2，3
        return 0;
    return a+1;
}

static void *thr_func(void *p){
    int n = (int)p;
    int ch = n+'a';
    while(1){
        pthread_mutex_lock(&mut);// 先抢🔒锁住自己的互斥量
        while(num!=n){ // 抢到锁，发现不是自己执行，就释放锁，等，出让调度器
            pthread_cond_wait(&cond_num,&mut);
        }
        write(1,&ch,1);
        num = next(num);
        // 打印完就松锁
        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut);// 🔓解锁下一线程对应的互斥量
    }
    pthread_exit(NULL);
}

int main(){
    int i,err;
    pthread_t tid[THRNUM];
    for(i = 0;i<THRNUM;i++){
        // 直接执行四个线程，不需要先锁住
        err = pthread_create(tid+i,NULL,thr_func,(void*)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);
        }
    }
    alarm(5);
    for(i = 0;i<THRNUM;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_cond_destroy(&cond_num);

    exit(0);
}