
#include <iostream>

struct ListNode {
   int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
       // 这个方法真的很好！
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        
        ListNode* pHeadList = nullptr;
        
        if(l1->val<l2->val){
            pHeadList = l1;
            pHeadList->next = mergeTwoLists(l1->next,l2);
        }else{
            pHeadList = l2;
            pHeadList->next = mergeTwoLists(l1,l2->next);
        }
        return pHeadList;
    }
};