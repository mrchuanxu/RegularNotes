#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void *func(void *p){
    puts("Thread is working.");
    sleep(10);
    pthread_exit(NULL); // 返回
}

int main(){
    pthread_t tid;
    int err;
    puts("Begin!");

    err =  pthread_create(&tid,NULL,func,NULL);
    if(err){
        fprintf(stderr,"pthread create():%s\n",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL);
    puts("End!");
    exit(0);
}