#include <iostream>
#include <vector>
using namespace std;
/***
 * 跳表实现
 * 多层分布
 * 直接寻找下一层
 * 每3个为一跳
 * 要知道怎么跳
 * 声明复合的数据结构
 * ***/

class SingleLinkList{
    public:
        int val;
        SingleLinkList *next;
        SingleLinkList *down;
        SingleLinkList() = default;
    private:
        SingleLinkList(const SingleLinkList&);
        SingleLinkList& operator=(const SingleLinkList&);
        
};

// 尾插法生成链表
SingleLinkList* insertRail(SingleLinkList *head,int val){
    auto tmp = head;
    while(tmp->next){
        tmp = tmp->next;
    } // O(n)
    SingleLinkList *newRail = new SingleLinkList();
    tmp -> next = newRail;
    newRail -> val = val;
    return head;
}

// 跳表实现 生成索引，每3个点生成一个索引，首次
SingleLinkList* produceLevelNode(SingleLinkList *head,int len){
     if(len/2<=1)
         return head;
     vector<SingleLinkList*> vecIndex; // 指针类型，存储index，暂存
     int numOfIndex = len>>1;
     while(head->next&&numOfIndex){
         SingleLinkList *index = new SingleLinkList();
         index -> val = head->val;
         index -> down = head;
         vecIndex.push_back(index);
         head = head->next->next;
         --numOfIndex; // 防止越界
     }
     for(int i = 1;i<len/2;++i){
         vecIndex[i-1]->next = vecIndex[i]; // 将索引相连接
     }
     head = vecIndex[0]; // 返回首指针
     return head;
};
//  查找跳表 
bool searchElemSkip(SingleLinkList *head,int elem){
    if(head->val == elem)
        return true;
    if(elem<head->val)
        return false;
    while(head){
        if(head->next){
        if(elem>=head->val&&elem<=head->next->val){
            if(head -> down){ // 一直往下跳，跳到最后
                head = head->down;
            }else{
                while(head){
                    if(head->val == elem){
                        return true;
                    }
                    head = head->next;
                }
            }
        }else if(elem>head->next->val&&head->next){
            head = head->next;
        }else {
            head = head->down;
        }
        }else
            head = head->down;
    }
    return false;
}
// 插入 需要重新生成层数或者再层数中插入新节点

int main(){
    SingleLinkList *skipNode = new SingleLinkList();
    int *arr = new int[10]{1,2,3,4,4,5,7,8,9,9};
    for(int i = 0;i<10;++i){
        skipNode = insertRail(skipNode,arr[i]);
    }
    // 生成多层skip level
    int len = 10;
    while(len){
       skipNode = produceLevelNode(skipNode,len);
       len = len>>1;
    }
    if(searchElemSkip(skipNode,4)){
        cout << "find!" << endl;
    }else{
        cout << "Ooops~" << endl;
    }
    return 0;
}



