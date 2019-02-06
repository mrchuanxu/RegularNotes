#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;
// class lval_box{
//     protected:
//         int val;
//         int low,high;
//         bool changed = false;
//     public:
//     lval_box(int ll,int hh):val(ll),low(ll),high(hh){}
//     virtual int get_value(){ changed = false;return val;}
//     virtual void set_value(int i){changed = true;val = i;}
//     virtual void reset_value(int i){changed = false;val = i;}
//     virtual void prompt(){}
//     virtual bool was_changed()const { return changed;}
//     virtual ~lval_box(){};
// };

struct Employee{
    string first_name,family_name;
    char middle_initial;
    string hiring_date;
    short department;
};

struct Manager:public Employee{
    list<Employee*> group;
    short level;
    //...
};

void g(){
    Employee *pe = new Employee();
    Manager *pm = static_cast<Manager*>(pe);
    pm->level = 12;
    cout << pm->level << endl;
    delete pe;
}

class Shape{
    public:
       virtual void draw(){
            cout << "i am shape" << endl;
        }
        virtual void nodraw() = 0;
        virtual ~Shape(){
            cout << "delete shape!" << endl;
        };
};


class Shape2{
    public:
    Shape2(){
        cout << "construct Shape2" <<endl;
    }
       virtual void draw(){
            cout << "i am shape2" << endl;
        }
        virtual ~Shape2(){
            cout << "delete shape2!" << endl;
        };
};


class Circle:public Shape,private Shape2{
    public:
        void print(){
            cout << "no circle" << endl;
        }
        void nodraw() override{
            cout << "no draw" << endl;
        }
        ~Circle(){
            cout << "delete shape?" << endl;
        }
};

template <class T>
struct Vector:std::vector<T>{
    using vector<T>::vector;
    T& operator[](size_t i){check(i);return this->elem(i);}
    const T& operator[](size_t i) const {check(i);return this->elem(i);}
    void check(size_t i){ 
        if(this->size() < i)
            throw range_error("Vector::check() failed");
    }
};

// template <typename T>
// class List{
//     public:
//     void insert(T&);
//     T get();
// private:
//     struct Link{
//     T val;
//     Link *next;
//     };
//     Link *head;

// };

// template<class T>
// T List<T>::get(){
//     Link *p = head;
//     head = p->next;
// }

// template <class T>
// class Set{
//     public:
//         bool member(const T& item) const;
//         void insert(const T& item);
//         void remove(const T& item);
//         std::size_t size() const;
//     private:
//         std::list<T> rep; // 用来表述Set的数据
// };

// template <class T>
// bool Set<T>::member(const T& item) const{
//     return find(rep.begin(),rep.end(),item) != rep.end();
// }

struct Storable{
    virtual string get_file() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Storable(){}
};

class Transmiitter:public Storable{
    public:
        void write() override{
            cout << "Transmitter" << endl;
        }
        void read() override{
            cout << "Transmitter read" << endl;
        }
        string get_file(){
            cout << "Transmitter getfile" << endl;
        }
};

class Receiver:public Storable{
    public:
        void write() override{
            cout << "Receiver" << endl;
        }
        void read() override{
            cout << "Receiver read" << endl;
        }
        string get_file(){
            cout << "Receiver getfile" << endl;
        }
};

class Radio:public Receiver,public Transmiitter{
    public:
        void write() override{
            cout << "Radio" << endl;
        }
        void read() override{
            cout << "Radio read" << endl;
        }
        string get_file() override{
            cout << "Radio getfile" << endl;
        }
};

#define size 10
char str[size],str2[size+2];
int main(){
    // Vector<int> v{1,2,3,4,5,6};
    // Employee *eman = new Manager();
    // eman->first_name = "mrtrans";
    // g();
    // delete eman;

    // Shape *cir = new Circle();
    // Circle *cir2 = new Circle();
    // cir->draw();
    // cir->nodraw();
    // Shape *b1 = (Shape*) cir2;
    // b1->draw();
    // delete cir;
    // Radio *ptr = new Radio();
    // ptr->Transmiitter::get_file();
    int num = 7,sum =7;
    sum = num++;
    sum++;
    ++num;
    cout << sum << endl;
    int n = 5;
    int a[n][n+2];
    return 0;
}