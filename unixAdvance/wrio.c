#include "./include/apue.h"

int main(void){
    // int c;
    // while((c=getc(stdin))!=EOF)
    //     if(putc(c,stdout)==EOF)
    //         err_sys("output error");
    // if(ferror(stdin))
    //     err_sys("input error");
    printf("hello world from process ID %ld\n",(long)getpid());
    exit(0);
}

