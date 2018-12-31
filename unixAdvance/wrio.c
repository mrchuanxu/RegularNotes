#include "./include/apue.h"

int main(void){
    // int c;
    // while((c=getc(stdin))!=EOF)
    //     if(putc(c,stdout)==EOF)
    //         err_sys("output error");
    // if(ferror(stdin))
    //     err_sys("input error");
    // printf("hello world from process ID %ld\n",(long)getpid());
    int n;
    char buf[4096];
    while((n=read(STDIN_FILENO,buf,4096))>0)
        if(write(STDOUT_FILENO,buf,n)!=n)
            err_sys("write error");
    
    if(n<0){
        err_sys("read_error");
    }
    exit(0);
}

