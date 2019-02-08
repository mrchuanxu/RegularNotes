#include "../include/apue.h"
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#define BUFSIZE 32

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 互斥量

static void *fun(void *p){
    int fd = -1;
    long long n = 0;
    char buf[BUFSIZE] = "";
    fd = open(p,O_RDWR|O_CREAT,0664);
    pthread_mutex_lock(&mutex); // 锁住互斥量
    printf("only one thread work!\n");
    read(fd,buf,BUFSIZE); // 读取
    lseek(fd,0,SEEK_SET); // 设置偏移量
    n = atoll(buf);
    snprintf(buf,BUFSIZE,"%lld\n",++n);// ➕1操作
    write(fd,buf,strlen(buf));

    close(fd);

    pthread_mutex_unlock(&mutex); // 解锁🔓资源
    pthread_exit(NULL); // 线程读完退出
}

int main(int argc,char **argv){
    int err;
    pthread_t tids[20];
    int i = 0;
    if(argc < 2){
        fprintf(stderr,"Usage %s<filename>\n",argv[0]);
        return -1;
    }
    for(i = 0;i<20;i++){
        err = pthread_create(&tids[i],NULL,fun,argv[1]);
        printf("pthread %d\n",i);
        if(err)
            err_exit(err,"create() error");
    }
    for(i = 0;i<20;i++){
        pthread_join(tids[i],NULL);
    }

    pthread_mutex_destroy(&mutex); //毁掉互斥量
    return 0;
}