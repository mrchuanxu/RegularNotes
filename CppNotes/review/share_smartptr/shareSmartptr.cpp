/***
 * 动态内存与智能指针
 * shared_ptr
 * weak_ptr
 * unique_ptr
 * ***/
#include <memory>
#include <iostream>

using namespace std;

int main(){
    shared_ptr<int> p3 = make_shared<int>(42);
    cout << *p3 << endl;
    return 0;
}