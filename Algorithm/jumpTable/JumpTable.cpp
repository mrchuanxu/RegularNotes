#include <iostream>

/***
 * 跳表实现
 * 多层分布
 * 直接寻找下一层
 * 每3个为一跳
 * 要知道怎么跳
 * 声明复合的数据结构
 * ***/

struct SingleLinkList{
    int val;
    SingleLinkList *next;
};

struct LevelNode{
    int val;
    LevelNode *next;
    LevelNode *down;
}