#include "../include/apue.h"

static void charatatimr(char *);

int main(void){
    pid_t pid;
    //TELL_WAIT();
    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid==0){
       // WAIT_PARENT();
        charatatimr("output from child\n");
    }else{
        sleep(10);
        charatatimr("out put from parent\n");
        //TELL_CHILD(pid);
    }
    exit(0);
}

static void charatatimr(char *ctr){
    char *ptr;
    int c;

    setbuf(stdout,NULL); // 将标准输出设置为不带缓冲，就是完全由内核调用输出，每个字符的输出都需要调用一次write
    for(ptr=ctr;(c=*ptr++)!=0;) // 逐个字符输出
        putc(c,stdout);
}