// #include <fcntl.h>
// #include <unistd.h>


// int creat(const char* path,mode_t mode);
// int close(int fd);
// off_t lseek(int fd,off_t offset,int whence);
#include "../include/apue.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int main(void){
    // if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)  //   测试为-1而不是0
    //     printf("can't seek");
    // else
    //     printf("seek ok!");
    char *str = "123abc456";
    int i = 0;
    i = atoi(str);
    printf("%d\n",i);
    exit(0);
}