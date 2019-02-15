/*定义双方都需要使用的数据或对象*/
#ifndef PROTO_H__
#define PROTO_H__
#define NAMESIZE 32
// 通讯双方生成key值共同使用的文件
#define KEYPATH "./test.txt"
// 通讯双方生成key值共同使用的salt值
#define KEYPROJ 'a'

// 消息类型，只要是大于0的合法整数即可
#define MSGTYPE 10

// 通讯双方约定的协议
struct msg_st{
    long mtype;
    char name[NAMESIZE];
    int math;
    int chinese;
};
#endif //  PROTO_H__