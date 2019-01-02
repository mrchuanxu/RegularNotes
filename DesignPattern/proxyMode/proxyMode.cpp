/***
 * 简单的代理模式
 * 找个人帮我打游戏
 * ***/
#include <iostream>
using namespace std;
class IGamePlayer{
    public:
    IGamePlayer(){}
    virtual void login(const string& name,const string &password) {
            cout <<  "who login?" << endl;
    }
    virtual void killBoss() {
            cout <<  "kill boss?" << endl;
    }
    virtual void upgrade() {
            cout <<  "upgrade?" << endl;
        }
    // private:
    // IGamePlayer(const IGamePlayer&);
    // IGamePlayer& operator=(const IGamePlayer&);
};


class GamePlayer:public IGamePlayer{
    public:
        GamePlayer(IGamePlayer *_gameplayer,const string &_name){
            if(_gameplayer==nullptr){
                throw runtime_error("no new object");
            }else{
                name = _name;
            }
        }
        virtual void login(const string& name,const string &password) override{
            cout << name << "login" << endl;
        }
        virtual void killBoss() override{
            cout << name << "kill boss" << endl;
        }
        virtual void upgrade() override{
            cout << name << "upgrade" << endl;
        }
    private:
       string name;
};

class IProxy{
    public:
       virtual void count()=0;
};
// 来个代练的
class GamePlayerProxy:public IGamePlayer,public IProxy{
    IGamePlayer *gameplayer;
    public:
        GamePlayerProxy(const string &_name){
            // gameplayer = igameplayer; // 这里的命名要是相同会产生segement fault的错误
            try{
                gameplayer=new GamePlayer(this,_name); // 在里面构造新对象，而且仅对某对象代理
            }catch(exception e){
                cout << e.what() << endl;
            }
        }
        virtual void login(const string& name,const string &password) override{
            gameplayer->login(name,password);
        }
        virtual void killBoss() override{
            gameplayer->killBoss();
           
        }
        virtual void upgrade() override{
           gameplayer->upgrade();
        }
        virtual void count() override{
            cout << "20 buckets thanks" << endl;
        }
};
/***
 * 普通代理
 * 普通代理 要求客户端只能访问代理角色，不能访问真实的角色
 * 
 * 强制代理
 * 强制你去找代理
 * 只能找代理处理
 * 代理也可以做一些自己的事情
 * 
 * 动态代理
 * 面向横切面编程
 * AOP
 * 采用动态代理机制
 * ***/
int main(){
    // IGamePlayer *player= new GamePlayer("Trans");
    // IGamePlayer *proxy = new GamePlayerProxy(player);
    // proxy->login("trans","123445");
    // proxy->killBoss();
    // proxy->upgrade();
    IGamePlayer *comproxy = new GamePlayerProxy("Mr Trans");
    comproxy->login("trans","12345");
    comproxy->killBoss();
    comproxy->upgrade();
    GamePlayerProxy gmp("Mr");
    gmp.login("123","123");
    gmp.killBoss();
    gmp.upgrade();
    gmp.count();
    return 0;
}