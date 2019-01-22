#include "../include/apue.h"

static void my_exit1(void){
    printf("go a");
    _exit(0);
}

static void my_exit2(void){
    printf("go b");
}

int main(void){
    puts("Begin!");
    if(atexit(my_exit2)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    puts("End!");
    return 0;
}