#include <iostream>
#include <string>

class GetInput {
  public:
     GetInput(std::istream &i = std::cin):is(i){}
     std::string operator()() const {
         std::string str;
         std::getline(is,str);
         return is?str:(std::string());
     }
  private:
     std::istream &is;
};
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
  ListNode* ReverseList(ListNode* pHead) {
        // 主要是不能断链！保存好链节点
        if(pHead == nullptr) return nullptr;
        ListNode *pNew;
        ListNode *pTmp;
        ListNode *pNext;
        while(pHead){
            pTmp = pHead->next;
            pHead->next = pNew;
            pNew = pHead;
            pHead = pTmp;
        }
        pHead = pNew;
        return pHead;
  }

int main(){
  GetInput getInput;
  std::cout << getInput() << std::endl;
  return 0;
}
