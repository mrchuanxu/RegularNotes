#include <iostream>
#include <string>
#include <map>
using namespace std;
/***
 * 实现栈的数据结构并且实现判断符号的对称性{[{[()]}]}
 * 顺序栈和链式栈
 * 后进先出
 * 定义pop和push
 * 支持动态扩容
 * 匹配所有string "[{()}]"的关系
 ***/

template <typename T> class StackUse{
  public:
    StackUse(T *array):arr(array){
    }
    T *arr; // 使用指针获得数组，实现动态扩容
    void push(T element); // 入栈
    T& pop(); // 出栈
    int length; // 记录栈的大小
    T element;
  private:
    StackUse(const StackUse&){}
    StackUse& operator=(const StackUse&){}
    int count = 0; // 出栈入栈计数
};

template <typename T> T& StackUse<T>::pop(){
    element = *arr;
    if(count > 0){
        --count;
        arr--;
    }else{
      return element;
    }
    return element;
}

template <typename T> void StackUse<T>::push(T element){
    if(count < length){
      ++arr; // 这里返回的是指针所指向
      *arr = element;
      ++count;
      cout << *arr << endl;
    }else{
      cout << "out of memory please expend the memory" << endl;
    }
    cout << "success!" << endl;
}

// 判断字符串是否对称
bool synicString(const string& str){
    if(str.size() == 0)
        return false;
    map<char,char> signal_count = {{'{','}'},{'[',']'},{'(',')'}};
    int str_half_size = str.size()/2;
    if(str.size()%2 != 0)
        return false;
    char ctr[str_half_size];
    StackUse<char> ictr(ctr);
    int i = 0;
    for(;i<str_half_size;i++){
      ictr.push(str[i]);
    }
    while(signal_count[ictr.pop()] == str[i]){
      ++i;
      if(i == str.size())
         return true;
    }
    return false;

}

int main(){
  char ctr[10];
  // cout << ctr << endl;
  StackUse<char> icr(ctr);
  icr.length = 10; // 支持动态扩容
  string istr = "";
  if(synicString(istr)){
    cout << "yes!" << endl;
  }else{
    cout << "Nope!" << endl;
  }
  // for(int i = 0; i<istr.size();i++){
  //     icr.push(istr[i]);
  // }
  // cout << icr.pop() << endl;
  // icr.push(insectr);
  // cout << icr.pop() << endl;

  // int inum[3] = {2,3,4};
  // int *p = inum;
  // int *&r = p;
  // cout << *(p+2) << endl;
  // cout << r << endl;
  // cout << inum << endl;
  // char ctr[3] = {'z','c','x'};
  // cout << *ctr << endl;
  // cout << *(ctr+1) << endl;
  return 0;
}
