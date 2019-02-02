/***
 * ELF文件
 * 连接试图与执行试图
 * 
 * 连接视图下，数据块的单位是节 多个节区索引所有内容
 * 执行视图下，数据块的单位是段 用程序头索引所有段
 * 
 * ***/
#include <stdio.h>
#include <stdlib.h>

static char static_data[16] = "I am static data";
static char raw_static_data[40960];
static const char const_data[16] = "i am const data";

int main(int args,char **argv){
    printf("message in main\n");
    return 0;
}