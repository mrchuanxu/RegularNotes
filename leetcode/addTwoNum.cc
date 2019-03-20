
#include <iostream>

/***
 * 两条链的拿捏
 * 其实就集中情况的考虑
 * 多写
 * ***/
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
  };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 用时间换空间的情况
        // 判断空条件 异常情况
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        // 主要是进位的拿捏
        int flag = 0; // 做进位标记
        ListNode* head = l1;
        while(l1&&l2){ // 这里走完最短的一条链
            int sum_l1_l2;
            // 考虑将sum值加到其中一条链，直接选l1
            if(flag){
            if((sum_l1_l2 = l1->val+l2->val+flag)>=10) {
                l1->val = sum_l1_l2%10;
                flag = 1;
            }
            else {
                l1->val = sum_l1_l2;
                flag = 0;
            }
            }else{
            if((sum_l1_l2 = l1->val+l2->val)>=10) {
                l1->val = sum_l1_l2%10;
                flag = 1;
            }
            else {
                l1->val = sum_l1_l2;
                flag = 0;
            }
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        if(flag){
            if(l2){
                l1 = head;
                while(l1->next){
                    l1 = l1->next;
                }
                l1->next = l2;
                int sum_flag_l2;
                // 这是末端的链条l2
                while(l2->next){
                    if(flag){
                        if((sum_flag_l2 = l2->val+1)>=10){
                            l2->val = sum_flag_l2%10;
                            flag = 1;
                        }else{
                            l2->val = sum_flag_l2;
                            flag = 0;
                        }
                    }
                    l2 = l2->next;
                }
                // 判断到l2的下一个节点为空，而flag还是为1则添加
                if(flag){
                    if((sum_flag_l2 = l2->val+1)>=10){
                         l2->val = sum_flag_l2%10;
                         ListNode* addFlag = new ListNode(1);
                        // 这里争取空间复杂度为1；
                         l2->next = addFlag;
                    }else{
                        l2->val = l2->val+1;
                    }
                }
            }else if(l1){
                int sum_flag_l1;
                while(l1->next){//这是末端链条1
                    if(flag){
                        if((sum_flag_l1 = l1->val+1)>=10){
                            l1->val = sum_flag_l1%10;
                            flag = 1;
                        }else{
                            l1->val = sum_flag_l1;
                            flag = 0;
                        }
                    }
                    l1 = l1->next;
                }
                // 判断l1下一个节点为空，而flag还是为1则添加节点
                    if(flag){
                    if((sum_flag_l1 = l1->val+1)>=10){
                         l1->val = sum_flag_l1%10;
                         ListNode* addFlag = new ListNode(1);
                        // 这里争取空间复杂度为1；
                         l1->next = addFlag;
                    }else{
                        l1->val = l1->val+1;
                        // flag = 0;
                    }
                }
            }else{ // 两端都没有了末尾
                l1 = head;
                while(l1->next){
                    l1 = l1->next;
                }
                ListNode* addFlag = new ListNode(1);
                // 这里争取空间复杂度为1；
                l1->next = addFlag;
            }
        }else{ // 标记不为1
            if(l2){ // 判断链末端
                l1 = head;
                while(l1->next){
                    l1 = l1->next;
                }
                l1->next = l2;
            }
        }
        l1 = head;
        return l1;
    }
};