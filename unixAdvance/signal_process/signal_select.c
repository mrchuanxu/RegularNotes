#include "../include/apue.h"
#include <sys/select.h>

int main(void){
    int i = 0;
    struct timeval timeout;

    for(i = 0;i<5;i++){
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
// 定时器只需要给定时间就可可以了
        if(select(0,0,0,0,&timeout)<0){
            err_sys("select()");
            exit(1);
        }
        printf("hehe\n");// 不写\n就会全缓冲
        // 写了\n就是行缓冲
    }
    return 0;
}