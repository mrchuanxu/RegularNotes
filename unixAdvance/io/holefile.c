#include "../include/apue.h"
#include <fcntl.h>
/***
 * od -c file.txt
 * 用来观察实际内容
 * ls -l file.txt 检查其大小
 * read 当从管道或FIFO读时，如若管道包含的字节少于所需的数量，那么read将只返回实际可用的字节数
 * 当一信号造成中断，而已经读了部分数据量时。
 * ***/
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
int main(void){
    int fd;
    int n;
    char buf[4096];
    if((fd = creat("file.hole",FILE_MODE))<0)
        err_sys("creat error");
    if(write(fd,buf1,10)!=10)
        err_sys("buf1 write error");
    
    if(lseek(fd,1010,SEEK_SET)==-1)
        err_sys("lseek error");
    
    if(write(fd,buf2,10)!=10)
        err_sys("buf2 write error");
    printf("%d",fd);
    exit(0);
}