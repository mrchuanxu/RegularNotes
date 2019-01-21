#include <memory>
#include <iostream>
#include <string>
#include <list>
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

//         typename add_lvalue_reference<element_type>::type operator*() const;
// };
// namespace transshare{
//     #include <iostream>
//     #include <string>
//     using namespace std;
//     template<typename U,typename D = default_delete<U> >
//     class shared_ptr{
//         public:
//             using element_type = U;
//             constexpr shared_ptr() noexcept;
//             constexpr shared_ptr(nullptr_t):shared_ptr(){} // 空对象
//             template <class U> explicit shared_ptr(U* p); // 显式构造 不存在隐式转换
//             template <class U,class D> shared_ptr(U* p,D del); // 添加释放器
//             template <class D> shared_ptr(nullptr_t p,D del); // 空指针的释放器
//             template <class U,class D, class Alloc> shared_ptr(U* p,D del,Alloc alloc); // 分配？
//             template <class D,class Alloc> shared_ptr(nullptr_t p,D del,Alloc alloc);
//             shared_ptr(const shared_ptr& x) noexcept;
//             template<class U> shared_ptr(const shared_ptr<U>& x)noexcept;
//             template<class U> explicit shared_ptr(const weak_ptr<U>& x);
//             shared_ptr(shared_ptr&& x)(shared_ptr<U>&& x)noexcept;
//             template <class U> shared_ptr(auto_ptr<U>&& x);
//             template <class U,class D> shared_ptr(unique_ptr<U,D>&& x);
//             template <class U> shared_ptr(const shared_ptr<U>& x,element_type* p)noexcept;
//     };
// };
void process(shared_ptr<int> &ptr){
    cout << ptr.use_count() << endl;
    cout << *ptr << endl;
}
struct Node{
    weak_ptr<Node> pPre;
    weak_ptr<Node> pNext;
    int val;
    Node(){
        cout << "construct" << endl;
    }
    ~Node(){
        cout << "delete" <<endl;
    }
};
void func(){
    shared_ptr<Node> p1(new Node());
    shared_ptr<Node> p2(new Node());
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
    p1->pNext = p2;
    p2->pPre = p1;
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;
}
void funcf(Node* p){
    cout << "hello world" <<endl;
}
void (*pf)(Node *p);
int main(){
    //unique_ptr<int> up(new int(12));
    // string *pstr = p1.get();
    // cout << *pstr << endl;
    //shared_ptr<string> ps(up);
    // int *inum = new int(42);
    // shared_ptr<int> p2(inum);
   // *p1 = "hi world";
    // if(p1->empty()){
    //      cout << "empty" << endl;
    // }
    // cout << *ps << endl;
    // string *inum = new string("hhh");
    // shared_ptr<string> p3 = make_shared<string>("hi");
    //  shared_ptr<string> p4 = make_shared<string>("hi");
    //   shared_ptr<string> p5 = make_shared<string>("hi");
    // cout << p3 << endl;
    // cout << p4 << endl;
    // p5.reset(inum);
    // auto r = p3;
    // cout << r.use_count() << endl;
    // shared_ptr<int> p6(up);
    // cout<< *p6 << endl;
    //func();
    auto deleter = [](Node* p){
    cout << "[deleter called]\n"; 
    //delete p;
    };
    // shared_ptr<int> foo (new int,deleter);
    // cout << "use_count: " << foo.use_count() << '\n';
    pf = funcf;
    shared_ptr<Node> bar(new Node(),pf);

    return 0;
}