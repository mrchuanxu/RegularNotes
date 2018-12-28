// #include <fcntl.h>
// #include <unistd.h>


// int creat(const char* path,mode_t mode);
// int close(int fd);
// off_t lseek(int fd,off_t offset,int whence);
#include "../include/apue.h"

int main(void){
    if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)  //   测试为-1而不是0
        printf("can't seek");
    else
        printf("seek ok!");
    exit(0);
}