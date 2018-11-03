#include <iostream>
#include <string>

#define data_type char

using namespace std;

class singleLink{
  public:
    singleLink() = default;
    data_type ctr;
    singleLink* next;
};
singleLink* singlelinkInsertHead(singleLink* linkList,data_type ctr){
  try{
    singleLink *hNode = new singleLink();
    hNode->ctr = ctr;
    hNode->next = linkList;
    return hNode;
  }catch(runtime_error err){
    cerr << err.what() << endl;
  }
}

singleLink* getMiddleNode(singleLink* linkList){
  try{
  singleLink* slow;
  singleLink* fast;
  slow = linkList;
  fast = linkList;
  while(fast&&slow){
    if(fast->next == NULL)
        return slow;
    else if(fast->next != NULL && fast->next->next == NULL)
        return slow;
    else{
      fast = fast->next;
      fast = fast->next;
      slow = slow->next;
    }
  }
  }catch(runtime_error err){
    cout << err.what() << endl;
  }
}

singleLink* reveseList(singleLink* head){
  singleLink *tmp;
  try{
    tmp = head->next;
    head->next = head;
  if(tmp->next != NULL){
    return reveseList(tmp);
  }else{
     return tmp;
  }
  }catch(runtime_error err){
    cerr << err.what() << endl;
  }
}
// 判断回文
bool isPalinedrome(const string &s){
  singleLink *head;
  singleLink *middle;
  singleLink *revese;
  head->next = NULL;
  try{
  for(auto c:s){
     head = singlelinkInsertHead(head,c);
  }
  middle = getMiddleNode(head);
  revese = reveseList(middle);
  while(revese->next != NULL){
    // cout << "?" << endl;
    if(revese->ctr == head->ctr){
        revese = revese->next;
        head = head->next;
    }else{
      return false;
    }
    return true;
  }
  }catch(runtime_error err){
    cerr << err.what() << endl;
  }
}

int main(){
  if(isPalinedrome("abba")){
    cout << "isPalinedrome" << endl;
  }else{
    cout << "not Palinedrome" << endl;
  }
  return 0;
};
