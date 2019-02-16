#ifndef PROTO_H__
#define PROTO_H__

#include <stdint.h>

#define RCVPORT "8089"
#define NAMESIZE 13

struct msg_st{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
}__attribute__((packed)); 
// 这里对齐
#endif