#include "../include/apue.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>

#include "proto.h"

int main(){
    key_t key;
    int msgid;
    struct msg_st sbuf;

    // 设置随机数种子
    srand(time(NULL));
    // 用于接收方相同的文件和salt生成一样的key
    key = ftok(KEYPATH,KEYPROJ);
    if(key<0) err_sys("ftok()");
    // 取得消息队列
    msgid = msgget(key,0);
    if(msgid<0) err_sys("msgget");

    // 要发送的结构体赋值
    sbuf.mtype = MSGTYPE;
    strcpy(sbuf.name,"Trans");
    sbuf.math = rand()%100;
    sbuf.chinese = rand()%100;

    if(msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0)<0) err_sys("msgsnd");
    
    puts("ok!");
    exit(0);
}