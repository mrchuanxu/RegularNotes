#include "../include/apue.h"

#define BSZ 48

int main(){
    FILE *fp;
    char buf[BSZ];
    memset(buf,'a',BSZ-2); // 在buf指定的缓冲区设置BSZ-2字节，每个初始化为a
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'x';
    if((fp=fmemopen(buf,BSZ,"w+"))==NULL)
        err_sys("fmemopen failed");
    printf("initial buffer contetnts:%s\n",buf);
    fprintf(fp,"hello,world");
    printf("brfore flush:%s\n",buf);// 在没有flush之前是怎样的
    fflush(fp);
    printf("after fflush:%s\n",buf);
    printf("len of streing in buf = %ld\n",(long)strlen(buf)); // 
    
    memset(buf,'b',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'x';
    fprintf(fp,"hello world");
    fseek(fp,0,SEEK_SET); // 显式地为一个打开文件设置一个偏移量
    printf("after fseek:%s\n",buf);
    printf("len of string in buf = %ld\n",(long)strlen(buf)); // 

    memset(buf,'c',BSZ-2); // 用c改写缓冲区
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'x';
    fprintf(fp,"hello world"); // 写到指定的流上
    fclose(fp); // 关闭流
    printf("after fclose:%s\n",buf);
    printf("len of string in buf = %ld\n",(long)strlen(buf)); // 
    exit(0);
    // 在mac ox unix没有对上这些的输出，所以，这又linux3.2.0支持内存流，其他没跟上
}