#include "../include/apue.h"
#include <pthread.h>
#include <string.h>

static void *func(void *p){
    puts("Thread is working.\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t tid;
    int err,i;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    // 修改每个线程的栈大小
    pthread_attr_setstacksize(&attr,1024*1024);

    for(i = 0;;i++){
        err = pthread_create(&tid,&attr,func,NULL); // attr就是修改后的线程属性
        if(err){
            err_sys("pthread_create()");
            break;
        }
    }
    printf("i = %d\n",i);
    pthread_attr_destroy(&attr);
    exit(0);
}