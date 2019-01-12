#include <iostream>
#include <vector>

using namespace std;

extern int &r3; //  呢个一直都唔系好识用

template<typename K,typename V>
class Map{
    public:
        V& operator[](const K&);
        pair<K,V>* begin(){return &elem[0];}
        pair<K,V>* end(){return &elem[0]+elem.size();}
    private:
        vector<pair<K,V> > elem;
};
template <class K,class V>
V& Map<K,V>::operator[](const K& k){
    for(auto &x:elem)
        if(k==x.first)
            return x.second;
    elem.push_back({K,V{}});
    return elem.back().second; // 返回新元素的默认值
}

int main(){
    int val = 1;
    int &r(val); // 初始化
    int x = r;
    r = 2;
    ++r;
    int *p = &r; // &r得到一个指向r所引对象的指针
    cout << p << endl;
    // double &dr = 1; // 需要的是一个左值 而不是一个右值
    const double &cdr(1); //  这里

    return 0;
}