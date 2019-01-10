#include <stdio.h>
#include "../include/apue.h"
#include <fcntl.h>

int main(){
    FILE *fp;
    // 打开或者创建一个文件
    int fd;
    if((fd = creat("./bits.txt",O_WRONLY))<0)
        err_sys("open false");
    close(fd);
    if((fp=fopen("./bits.txt","r+"))<0){
        err_sys("open error");
    }
    float data[10];
    data[2] = 12.3;
    data[3] = 23.4;
    data[4] = 45.2;
    data[5] = 36.7;
    if(fwrite(&data[2],sizeof(float),4,fp)!=4)
        err_sys("fwrite error");
    fclose(fp);
    exit(0);
}