#include "../include/apue.h"
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(void){
    key_t key;
    int msgid;
    struct msg_st rbuf;

    // 通过/tmp/out文件和字符'a'生成唯一的key，文件必须真实存在
    key = ftok(KEYPATH,KEYPROJ); // 来自proto.h
    if(key<0) err_sys("ftok()");
    
    // 接收端先启动，所以消息队列由接收端创建
    if((msgid = msgget(key,IPC_CREAT|0600))<0) err_sys("msgget");
    
    // 不停的接收消息 轮询
    while(1){
        // 没有消息就会阻塞等待
        if(msgrcv(msgid,&rbuf,sizeof(rbuf)-sizeof(long),0,0)<0) err_sys("msgrcv");

        /***
         * 用结构体中强制添加的成员判断消息类型
         * 当然这个栗子只有一种消息类型，所以不判断也可以
         * 如果包含多种消息类型就可以协议组switch ...case结构
         * ***/
        if(rbuf.mtype == MSGTYPE){
            printf("Name = %s\n",rbuf.name);
            printf("Math = %d\n",rbuf.math);
            printf("Chinese = %d\n",rbuf.chinese);

        }
    }
    /***
     * 谁创建谁销毁
     * 这个程序无法正常结束只能等信号杀死
     * 使用信号杀死之后可以用ipcs命令查看，消息队列应该没有被销毁
     * 使用ipcrm删掉
     * ***/
    msgctl(msgid,IPC_RMID,NULL); // 销毁
    exit(0);
}