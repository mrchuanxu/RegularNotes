#include "../include/apue.h"
#include <fcntl.h>
/***
 * od -c file.txt
 * 用来观察实际内容
 * ls -l file.txt 检查其大小
 * read 当从管道或FIFO读时，如若管道包含的字节少于所需的数量，那么read将只返回实际可用的字节数
 * 当一信号造成中断，而已经读了部分数据量时。
 * ***/
char buf1[] = "qwertyuyui";
char buf2[] = "ABCDEFGHIJ";
int main(void){
    int fd; // 文件描述符 非负整数
    int n;
    char buf[4096];
    char bufread[4096];
    /***
     *  creat之后，就会有这个文件描述符fd
     * 然后可以在这个文件描述符进行write操作
     * lseek文件偏移量尾端的查找
     * 然后往文件偏移量的尾部继续写文件
     * ***/
    if((fd = creat("testfile.txt",FILE_MODE))<0)
        err_sys("create error");
    printf("%d",fd);
    if(write(fd,buf1,10)!=10) // 这里返回的是什么，返回的是所写的字节数！！！
        err_sys("buf1 write error");
    if(lseek(fd,10,SEEK_SET)==-1) // 这里返回的是什么？返回的是写完之后的文件偏移量
        err_sys("lseek error"); // 上面的1010是offset 就是距文件开始处的offset个字节
    if(write(fd,buf2,10)!=10)
        err_sys("buf2 write error");
    //printf("%d",fd);
    int sre;
    while((sre = read(STDIN_FILENO,bufread,4096))>0){
        if(write(fd,bufread,sre)!=sre) // 从标准输入读，读到文件描述符的文件中！
            err_sys("write error");
    }

    if(sre<0)
        err_sys("read error");
    //printf("%d\n",sre);
    exit(0);
}