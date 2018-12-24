/***
 * author: Mr.Trans(MT)
 * Date finish: 2018 12 24
 * use for:
 * 仅此用来解决散列表与链表的结合
 * 即链表法解决散列冲突
 * 链表法解决散列冲突即：每个桶或者槽位都会有一个对应的链表
 * 所有散列值相同的元素会放在相同的槽位或者桶对应的链表后面
 * 如果所有散列值相同的元素都放在同一个链表中，那就要想办法将这个元素的插入按顺序排序
 * 那么在lru缓存算法中，通过维护一个散列表和双向链表的操作，可以实现O(1)的查找，删除和添加
 * 在查找，删除，添加操作中，需要维护散列表解决冲突的链表，解决按顺序插入元素的双向链表
 * 
 * 每次查找的是元素，不是散列值
 * 以下将实现LRU缓存淘汰策略
 * ***/

/***
 * 首先定义一个双向链表以及一个单链表组成的节点 就是一个具有三个指针的节点
 * 然后就构成一个有两个链表的形式
 * ***/
/***
 * 还要考虑一个问题
 * template不存在隐式转换
 * ***/

#ifndef HASH_MAP_HEAD_H
#define HASH_MAP_HEAD_H
#include <iostream>
using namespace std;
template <typename T>
class TriNode{
    public:
    TriNode():t_Npre(nullptr),t_Hnext(nullptr),t_Nnext(nullptr){}
    T d_Nval;
    TriNode *t_Npre;
    TriNode *t_Nnext;
    TriNode *t_Hnext;
};

/***
 * 实现一个数组指针的节点
 * ***/

/***
 * 实现一个数组分槽
 * ***/
template <typename T>
class HashMapLru
{
  public:
    // 构造函数
    HashMapLru()
    {
    }
    // 散列函数 查到相应的槽位
    int hash_value_to_key(const T &value);
    // 遍历查找是否存在该元素
    // 存在即移到尾部
    // 不存在直接添加到尾部
    // 这个过程要维护 双向链表和单链表
    bool hash_value_addto_key(const T &value);
    // 查找值
    // 查到该值直接移动到尾部
    // 否则返回没有这个值
    bool hash_value_find(const T &value);
    // 删除 查到该元素直接删除，查不到就返回null 并且维护链表
    bool hash_value_delete(const T &value);
    // 查找这个过程可以用函数指针实现 直接查找返回，扩展实现
    TriNode<T> *look_value(const T &value); // 用int 记录状态
  private:
    // 拷贝构造函数
    HashMapLru(const HashMapLru &);
    // 赋值运算符
    HashMapLru &operator=(const HashMapLru &);
    TriNode<T> arrPtr[15]; // 散列表 长度为15的散列表数组，每个数组都是指定一个节点，每个指针都是指向一条链
    TriNode<T> *railPtr = nullptr;  // 维护一个尾节点；
};
// 散列函数 简单求余
template <typename T>
int HashMapLru<T>::hash_value_to_key(const T &value)
{
    int key = value % 15;
    return key;
}
// 考虑查找的问题 先写这个查找的方法 用于以上每个函数的使用
template <typename T>
TriNode<T> *HashMapLru<T>::look_value(const T &val)
{
    int key = hash_value_to_key(val);
    if (arrPtr[key].t_Hnext == nullptr)
        return nullptr; // 没找到这个元素
    TriNode<T> *valList = arrPtr[key].t_Hnext;
    while (valList)
    {
        if (valList->d_Nval == val)
        {
            return valList;
        }
        valList = valList->t_Hnext;
    }
    return nullptr;
}
// 查找一个元素
template <typename T>
bool HashMapLru<T>::hash_value_find(const T &value)
{
    // TODO: 考虑边界问题 链表中只有一个节点
    TriNode<T> *findNodeVal = look_value(value);
    int key = hash_value_to_key(value);
    if (findNodeVal != nullptr)
    {
        if(findNodeVal->t_Nnext == nullptr){
            return true;
        } // 仅有一个节点和尾节点
        TriNode<T> tracMovBackNode = *findNodeVal;
        // 断链 重组
        TriNode<T> *valPreNode = findNodeVal->t_Npre;
        TriNode<T> *valNxtNode = findNodeVal->t_Nnext;
        valPreNode->t_Nnext = valNxtNode;
        valNxtNode->t_Npre = valPreNode;
        // 复制后面的节点实现删除 O(1)
        if(findNodeVal->t_Hnext==nullptr){
                railPtr->t_Nnext = findNodeVal;
                findNodeVal->t_Npre = railPtr;
                findNodeVal->t_Nnext = nullptr;
                railPtr = findNodeVal;
                return true;
        }else{
                findNodeVal->t_Npre = findNodeVal->t_Hnext->t_Npre;
                findNodeVal->t_Nnext = findNodeVal->t_Hnext->t_Nnext;
                findNodeVal->t_Hnext->t_Npre->t_Nnext = findNodeVal;
                findNodeVal->t_Hnext->t_Nnext->t_Npre = findNodeVal;
                findNodeVal->d_Nval = findNodeVal->t_Hnext->d_Nval;
                auto *tmp = findNodeVal->t_Hnext;
                findNodeVal->t_Hnext = findNodeVal->t_Hnext->t_Hnext;
                delete tmp;
        }
        // 维护单链表
        while (findNodeVal->t_Hnext)
        {
            findNodeVal = findNodeVal->t_Hnext;
        }
        findNodeVal->t_Hnext = &tracMovBackNode;
        tracMovBackNode.t_Hnext = nullptr;
        // 维护双向链表
        while (findNodeVal->t_Nnext)
        {
            findNodeVal = findNodeVal->t_Nnext;
        }
        findNodeVal->t_Nnext = &tracMovBackNode;
        tracMovBackNode.t_Npre = findNodeVal;
        tracMovBackNode.t_Nnext = nullptr;
        railPtr = &tracMovBackNode; // 维护一个尾指针
        return true;
    }
    return false;
}
// 考虑边界问题 散列函数编码有多种多样
template <typename T>
bool HashMapLru<T>::hash_value_addto_key(const T &value)
{
    // 求key
    // TODO: 判断是否类型一致 边界问题
    int key = hash_value_to_key(value);
    TriNode<T> *findValue = look_value(value);
    // TODO: 这里要检查缓存是否满了，没满就往里面加否则删除头节点，然后往后面加
    if (findValue == nullptr)
    { // 没有这个元素 往最后添加
        TriNode<T> *triNode = new TriNode<T>();
        TriNode<T> *triArrPtrNode = new TriNode<T>();
        triNode->d_Nval = value;
        if (arrPtr[key].t_Hnext == nullptr)
        { // TODO: 这里检查第一个节点是否存在，不存在即将节点作为拉链的头节点
            arrPtr[key].t_Hnext = triNode;
            // 维护双链表 维护一个尾节点
            if (railPtr == nullptr)
            {
                triNode->t_Npre = &arrPtr[key];
                railPtr = triNode;
            }
            else
            {
                railPtr->t_Nnext = triNode;
                triNode->t_Npre = railPtr;
                railPtr = triNode; // 重新将指针指向
            }
            return true;
        }
        else
        {
            triArrPtrNode = arrPtr[key].t_Hnext; // 这里获取双链表的节点，只要持续遍历下去就可以获得尾节点
            // 维护双链表
            while (triArrPtrNode->t_Nnext)
            {
                triArrPtrNode = triArrPtrNode->t_Nnext;
            }
            triArrPtrNode->t_Nnext = triNode;
            triNode->t_Npre = triArrPtrNode;
            // 维护单链表
            triArrPtrNode = arrPtr[key].t_Hnext; // 这里是获取单链表的头节点
            while (triArrPtrNode->t_Hnext)
            {
                triArrPtrNode = triArrPtrNode->t_Hnext;
            }
            triArrPtrNode->t_Hnext = triNode;
            railPtr = triNode; // 维护一个尾指针
            return true;
        }
    }
    else if (findValue != nullptr)
    {
        return hash_value_find(value);
    }
    return false;
}

// 删除一个节点
template <typename T>
bool HashMapLru<T>::hash_value_delete(const T &value)
{
    TriNode<T> *findNodeVal = look_value(value);
    int key = hash_value_to_key(value);
    if (findNodeVal != nullptr) // TODO:
    {
        if(findNodeVal->t_Nnext == nullptr){
            railPtr = findNodeVal->t_Npre; // 维护双链表中的尾节点
            railPtr->t_Nnext = nullptr;
            // 仅有一个节点
        }else{
        // 断链 重组
            TriNode<T> *valPreNode = findNodeVal->t_Npre;
            TriNode<T> *valNxtNode = findNodeVal->t_Nnext;
            valPreNode->t_Nnext = valNxtNode;
            valNxtNode->t_Npre = valPreNode;
        }
        // 复制后面的节点实现删除 O(1)
        if(findNodeVal->t_Hnext!=nullptr){
        findNodeVal->t_Npre = findNodeVal->t_Hnext->t_Npre;
        findNodeVal->t_Nnext = findNodeVal->t_Hnext->t_Nnext;
        findNodeVal->t_Hnext->t_Npre->t_Nnext = findNodeVal;
        findNodeVal->t_Hnext->t_Nnext->t_Npre = findNodeVal;
        findNodeVal->d_Nval = findNodeVal->t_Hnext->d_Nval;
        auto *tmp = findNodeVal->t_Hnext;
        findNodeVal->t_Hnext = findNodeVal->t_Hnext->t_Hnext;
        delete tmp;
        return true;
        }else{
            delete findNodeVal;
        }
    }
    return false;
}
#endif // !HASH_MAP_HEAD_H