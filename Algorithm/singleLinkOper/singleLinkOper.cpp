#include <iostream>
#include <string>

#define data_type char
using namespace std;

// 建立单链表结构
class singleLink{
  public:
      singleLink() = default;
      data_type ctr;
      singleLink* next; // 指向下一个指针
      ~singleLink();
};
singleLink::~singleLink(){
   ctr = NULL;
   next = NULL;
}
// 初始化头节点
singleLink* initSingleLink(){
  singleLink *head = new singleLink(); // 动态申请空间，堆内存
  head->next = NULL;
  return head;
}

// 头插法插入生成链表
singleLink* insertHead(singleLink *head,const string &str){
  if(str.size() == 0)
    return head;
  for(int i = 0; i<str.size();i++){
    singleLink *pstr = new singleLink();
    pstr->ctr = str[i];
    pstr->next = head;
    head = pstr;
  }
  return head;
}

// 尾插法插入生成链表
singleLink* insertRail(singleLink *head,const string &str){
  if(str.size() == 0)
      return head;
  for(int i = 0; i<str.size();i++){
    singleLink *pstr = new singleLink();
    pstr->ctr = str[i];
    auto tmp = head;
    while(tmp->next){
      tmp = tmp->next;
    }
    tmp->next = pstr;
  }
  return head;
}

// 插入到某个位置
bool insertElement(singleLink *head, int n, data_type elem){
    if(n<0)
      return false;
    int i = 0;
    while(i<n&&head->next){ // 假设没有合适的位置，直接在尾部插入
      head = head->next;
      i++;
    }
    singleLink *pelem = new singleLink();
    pelem->next = head->next;
    pelem->ctr = elem;
    head->next = pelem;
    return true;
}

// 删除某个位置元素
bool deleteElement(singleLink *head, int n){
  if(n<0)
    return false;
  int i = 0;
  while(i<n && head){
    i++;
    head = head->next;
  }
  delete head->next; // 释放指针内存空间
  head->next = head->next->next;
  return true;
}

// 翻转链表
// singleLink* reverseLink(singleLink *head, singleLink *reveseNode){
//   if(head == NULL)
//       return head;
//   if(head->ctr == NULL)
//       head = head->next;
//   auto tmp = head->next;
//   head->next = reveseNode;
//   if(tmp){
//     return reverseLink(tmp,head);
//   }else{
//     return head;
//   }
// }
// 反转 非递归
singleLink* reverseLink(singleLink *pHead){
  if(pHead == nullptr) return nullptr;
        singleLink *pNew;
        singleLink *pTmp;
        while(pHead){
            pTmp = pHead->next;
            pHead->next = pNew;
            pNew = pHead;
            pHead = pTmp;
        }
        pHead = pNew;
        return pHead;
}
// 检测回文字符串
bool verifyPalindrome(singleLink *head,singleLink *mid){
    bool isPalindrome = false;
    if(head->ctr == NULL){
      head = head->next;
    }
    while(mid){
      if(mid->ctr != NULL){
        if(mid->ctr == head->ctr){
          isPalindrome = true;
        }else{
          isPalindrome = false;
          break;
        }
        head = head->next;
      }
      mid = mid->next;
    }
  return isPalindrome;
}
// 快慢指针获取中间节点
singleLink* midleNode(singleLink *head){
  singleLink *ps; // 这里的声明在栈中，会在出了局部作用域自动销毁
  singleLink *pf;
  if(head->ctr == NULL){
    head = head->next;
  }
  ps = pf = head;
  while(pf->next){
    if(pf->next->next){
        ps = ps->next;
        pf = pf->next->next;
    }else{
      break;
    }
  }
  if(pf->next){
    return ps->next;
  }else{
    return ps;
  }
    // delete ps;
    // delete pf;
}
// 两个有序链表合并  空间复杂度 O(1) 时间复杂度 O(n)
  //   singleLink* Merge(singleLink* pHead1, singleLink* pHead2)
  //   { 
  //       if(pHead1==nullptr||pHead2==nullptr) return nullptr;
  //       // 合并，就合并，不需要新增加什么
  //       singleLink* p1;
  //       singleLink* p2;
  //       singleLink* tHead;
  //       if(pHead1->ctr>pHead2->ctr){
  //           tHead = pHead2;
  //           p1 = pHead2; // p1是第一条链表
  //           p2 = pHead1;
  //       }else{
  //           tHead = pHead1;
  //           p1 = pHead1; // p1是第一条链表
  //           p2 = pHead2;
  //       }
  //       singleLink* tmp;
  //       while(p1&&p2){
  //           if(p1->ctr <= p2->ctr){
  //               if(p1->next->ctr>p2->ctr){
  //                   tmp = p2->next;
  //                   p2->next = p1->next;
  //                   p1->next = p2;
  //                   if(tmp != nullptr)
  //                        p2 = tmp; // p2往后走
  //                   else
  //                       p2 = nullptr;
  //               }
  //           }
  //           p1=p1->next;
  //           if(p1->next == nullptr&&p2!=nullptr){
  //               p1->next = p2;
  //               break;
  //           }else if(p2==nullptr) break;
  //       }
  //       pHead1 = tHead;
  //       return pHead1;
  // }
  singleLink* Merge(singleLink* pHead1,singleLink* pHead2){
        if(pHead1==nullptr&&pHead2!=nullptr) return pHead2;
        if(pHead1!=nullptr&&pHead2==nullptr) return pHead1;
        if(pHead1->ctr > pHead2->ctr){
              swap(pHead1,pHead2);
          }
        singleLink* tHead = pHead1;
        singleLink* tmp;
        while(pHead1&&pHead2){
            if(pHead1->next == nullptr&&pHead2!=nullptr) {
              pHead1->next = pHead2;
              break;
            }
            if(pHead1->ctr<=pHead2->ctr){
                if(pHead1->next->ctr>pHead2->ctr){
                    tmp = pHead2->next;
                    pHead2->next = pHead1->next;
                    pHead1->next = pHead2;
                    pHead2 = tmp;
                }
            }
            pHead1 = pHead1->next;
            if(pHead2 == nullptr) break;
        }
        pHead1 = tHead;
        return pHead1;
  }

int main(){
  singleLink *head = new singleLink();
  head = initSingleLink();
  head = insertRail(head,"135");
  singleLink *rlsit = new singleLink();
  rlsit = initSingleLink();
  rlsit = insertRail(rlsit,"135");
  head = Merge(head,rlsit);
  while(head){
    cout << head->ctr << endl;
    head = head->next;
  }
  // head = 
  // singleLink *mid = new singleLink();
  // mid = midleNode(head);

  // //if(insertElement(head,4,'D')){
  // singleLink *reveseNode = new singleLink();
  // reveseNode = reverseLink(head);
  // while(reveseNode){
  //   cout << reveseNode->ctr << endl;
  //   reveseNode = reveseNode->next;
  // }
  // if(verifyPalindrome(head,reveseNode)){
  //   cout << "yes,is palindrome" << endl;
  // }else{
  //   cout << "nope, it is not" << endl;
  // }
  // while(reveseNode){
  //   if(reveseNode->ctr!=NULL){

  //   }
  //   head = head->next;
  //   reveseNode = reveseNode->next;
  // }
  // while(head){
  //   cout << head->ctr << endl;
  //   head = head->next;
  // }
  // }
  return 0;
}
