#include <memory>
#include <iostream>
#include <string>
using namespace std;
/***
 * 模版类
 * 特例化
 * ***/

// template<typename T,typename D = default_delete<T> >
// class Unique_ptr{
//     public:
//         using pointer = ptr;
//         using element_type = T;
//         using deleter_type = D;
//         constexpr Unique_ptr() noexcept;
//         constexpr Unique_ptr(nullptr_t) noexcept:Unique_ptr(){} // 空指针类型
//         explicit Unique_ptr(pointer p) noexcept; // from pointer
//         Unique_ptr(pointer p,typename conditional<is_reference<D>::value,D,const D&> del) noexcept; // lvalue
//         Unique_ptr(pointer p,typename remove_reference<D>::type&& del) noexcept; // rvalue
//         Unique_ptr(Unique_ptr&& x) noexcept;// 右值 移动构造函数
//         template<class U,class E>
//             Unique_ptr(Unique_ptr<U,E>&& x)noexcept; // 特例化
//         template<class U>
//             Unique_ptr(auto_ptr<U>&& x)noexcept; // 不抛出异常
//         Unique_ptr(const Unique_ptr&) = delete; // 不允许拷贝

//         Unique_ptr& operator=(Unique_ptr&& x) noexcept; // 移动赋值运算
//         Unique_ptr& operator=(nullptr_t) noexcept; // 空指针类型
//         template<class U,class E>
//             Unique_ptr& operator=(Unique_ptr<U,E>&& x)noexcept; // 强制类型转换
//         Unique_ptr& operator=(const Unique_ptr&) = delete; // 不允许赋值

//         void reset(pointer p = pointer()) noexcept;// 这里有一个默认值
//         deleter_type& get_deleter() noexcept;
//         const deleter_type& get_deleter() const noexcept;
// };
int main(){
    int a();
    cout << *a << endl;
    unique_ptr<string> p1(new string("hello world"));
    string *pstr = p1.get();
    cout << *pstr << endl;
    return 0;
}