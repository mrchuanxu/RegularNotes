#include <stdio.h>

struct BinaryNode{
    int val;
    BinaryNode *pLeft;
    BinaryNode *pRight;
}BinaNode,*BiNode;

/***
 * struct的使用
 * strut是一个结构体
 * 声明里面的所有都是public
 * 现在在下面弄BinaNode,相当于声明了一个BinaryNode BinaNode对象
 * 指针 声明一个指针，但是没有实例化，使用的时候需要实例化
 * 相当于 BinaryNode *BiNode = new BiaryNode();
 * ***/
struct {
    int val;
}Node;
/***
 * 也就是说明了一个结构为Node的结构
 * 这个的后面不能加指针，否则就成为无媒媾合
 * 没有类型的指针
 * ***/

int main(){
    BinaNode.val = 12;
    printf("%d\n",BinaNode.val);
    BiNode = new BinaryNode();
    BiNode->val = 42;
    printf("%d\n",BiNode->val);
    Node.val = 32;
    printf("%d\n",Node.val);
    return 0;
}