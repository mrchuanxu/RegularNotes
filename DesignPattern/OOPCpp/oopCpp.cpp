#include <iostream>
#include <string>
using namespace std;
/***
 * 首先搞清楚继承
 * 基类 虚函数
 * 所以虚函数必须要有自己的实现***/
class Quote{
    public:
       Quote() = default;
       string isbn() const;
       virtual double net_price() const = 0;
};

class Bulk_quote:private Quote{
    public:
        Bulk_quote():Quote(){

        }
        double net_price() const override;
    private:
        double num = 12.33;
};

double Bulk_quote::net_price() const{
    return num;
}

int main(){
    Bulk_quote *bulk_qupte = new Bulk_quote();
    cout << bulk_qupte->net_price() << endl;
    return 0;
}


