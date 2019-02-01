#include "../include/apue.h"
#include <unistd.h>

int main(){
    pid_t pid;
    pid = getpgrp();
    printf("gid = %d\n",pid);
    return 0;
}