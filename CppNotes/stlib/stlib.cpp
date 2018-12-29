#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <regex>
#include <random>
#include <iomanip>

using namespace std;
/***
 * 可以利用tuple返回多个值
 * bitset位运算变得容易
 * 使用正则表达式regex
 * random 定义为static 引擎才能生成不同的序列 引擎要在循环外定义，不然保持不了状态
 * 使用io库
 * seek与tell 读取文件任意位置
 * 
 * ***/

int main(){
    tuple<int,double,float,string> t(1,1.23,1.44,"fuck you");
    cout << get<2>(t)*0.8 << endl;
    typedef decltype(t) trans;
    size_t sz = tuple_size<trans>::value;
    cout << sz << endl;

    tuple<string,vector<string>,pair<string,int>> tsvp("fuck off",{"no way"},{"yes",1});
    cout << get<1>(tsvp)[0] << endl;

    bitset<32> bitvec(1U);
    bitset<13> bitvec1(0xbeef);
    cout << bitvec1<<endl;
    bitset<16> bitvec2(9);
    cout << bitvec2 << endl;
    bitvec2.flip();
    cout << bitvec2 << endl;
    bitvec2.set(bitvec2.size()-1,0);
    cout << bitvec2 << endl;
    bitset<30> quizB;
    quizB.set(27);
    cout << quizB << endl;
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*"+pattern+"[[:alpha:]]*";
    regex r(pattern,regex::icase);
   // smatch results;
    string test_str = "receipt freind theif receive";
    for(sregex_iterator it(test_str.begin(),test_str.end(),r),end_it;it!=end_it;++it){
        cout << it->str() << endl;
    }
    uniform_int_distribution<unsigned> u(0,9);
    default_random_engine e;
    for(size_t i =0; i<10;++i){
        cout << u(e) << endl;
    }
    uniform_real_distribution<double> u1(0,1);
    default_random_engine ran;
    for(size_t i =0; i<10;++i){
        cout << u1(ran) << endl;
    }
    char resp;
    // bernoulli_distribution be(0.55);
    // do{
    //     bool fisrt = be(e);
    //     cout << (fisrt?"We go first":"you go first") <<endl;
    // }while(cin >> resp && resp[0] == 'y');
    bool bool_val = true;
    cout << boolalpha << bool_val << noboolalpha;
    cout << showbase;
    cout << oct << 20 << endl;
    cout << hex << 20 << noshowbase<<endl;
    //cout << dec <<20<<noshowbase;
    cout<<cout.precision(12)<<sqrt(2.0)<<endl;
    while(cin.get(resp))
        cout.put(resp);
    return 0;
}