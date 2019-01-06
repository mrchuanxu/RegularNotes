#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../include/apue.h"

FILE *fopen(const char *path,const char *mode);
int fclose(FILE *fp); // 与fopen对应，使用完一个文件之后，就要调用fclose函数
// 释放相关的资源，否则会造成内存泄漏。
int fgetc(FILE *stream); // 从输入流stream中读取一个字符串回填到s所指向的空间
char *fgets(char *s,int size,FILE *stream); // stream 通常是要么没有数据，要么一下子来一坨数据

size_t fread(void *ptr,size_t size,size_t nmemb,FILE *stream);
int main(void){
    FILE *fpth;
    fpth = fopen("./iofile.c","r+");
    if(fpth == NULL){
        err_quit("error open file");  
    }
    fgetc(fpth);
    fclose(fpth);
    return 0;
}