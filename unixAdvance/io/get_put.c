#include "../include/apue.h"
#include <stdio.h>
/***
 * 搞清楚，是对一个流操作
 * 而不是一个文件
 * ***/
int main(void){
    int c;
    FILE *fp;
    fp = freopen("./file.txt","r+",stdin); // 指定为输入流
    char  buf[3];
    while(fgets(buf,2,stdin)!=NULL) // 输入一行
        if(fputs(buf,stdout)==EOF) // 输出一行
                err_sys("output error");
   // printf("%s\n",buf);
    if(ferror(fp))
        err_sys("gets error");
    // if(feof(fp))
    //     err_sys("end of file");
    fclose(fp);
    exit(0);
}