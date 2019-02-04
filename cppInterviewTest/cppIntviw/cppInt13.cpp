#include <iostream>
#include <string>
#include <list>

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
        virtual ~Shape(){
            cout << "delete shape!" << endl;
        };
};

class Circle:public Shape{
    public:
        ~Circle(){
            cout << "delete shape?" << endl;
        }
};
int main(){
    Employee *eman = new Manager();
    eman->first_name = "mrtrans";
    g();
    delete eman;

    Shape *cir = new Circle();
    delete cir;
    return 0;
}