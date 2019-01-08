接下来，我们看看这7中 结构类模式的pk<br>
分别是 适配器模式、桥梁模式、组合模式、装饰模式、门面模式、享元模式和代理模式<br>
## 适配器模式 你们打架了？我来调和吧！
将一个类的接口变换成客户端多期待的另一种接口，从而使原本因接口不匹配而无法在一起工作的两个类能够在一起工作。<br>
适配器模式又叫做变压器模式。<br>
cpp可以实现多继承，来实现适配器模式，进行多重继承，有助于让两个类可以一起工作。<br>
这只是一种补救的模式，所以一般设计的时候不考虑。<br>
## 桥梁模式 抽象和实现分离
将接口与实现分离。这是出自于cpp effective的一句话，让两者解耦，使得两者可以独立地变化。<br>
4个角色：
* 抽象化角色<br>
定义出角色的行为，同时保存一个对实现化角色的引用，一般是抽象类
* 实现化角色<br>
接口或抽象类，定义角色所需要的行为和属性
* 修正抽象化角色<br>
引用是实现化角色对抽象化角色进行修正
* 具体实现化角色<br>
实现接口或抽象类定义的方法和属性<br>
抽象角色引用实现角色，或者说抽象角色的部分实现是由实现角色完成的。<br>
```cpp
class Implementor{};
class ConcreImplementor:private Implementor{}; // 实现化角色
class Abstraction{ // 抽象化角色
    public:
        Abstraction(Implementor _imp){
            imp = _imp;
        }
        void request(){
            imp....
        }
        Implementor getImp(){
            return imp;
        }
    private:
        Implementor imp;
};
class Refined:public Abstraction{
    public:
        Refined(Implementor _imp):Abstraction(_imp){};
        void request(){
            Abstraction::request();
            Abstraction::getImp()...;
        }
};
```
使用了类间的聚合关系、继承、覆写等常用功能。<br>
* 抽象和实现分离<br>
完全解决了继承的缺点
* 优秀的扩充能力
* 实现细节对客户透明
客户不同关心细节，已经由抽象层通过聚合关系完成封装。<br>
不要强侵入。<br>
考虑桥梁模式经常用于应为有多重继承，多重继承可以考虑一下桥梁模式。<br>
将抽象和实现分离。<br>
## 组合模式 我只是整体的一部分(一棵树的🌰)
将对象组合成树形结构以表示“部分-整体”的层次结构，使得用于对单个对象和组合对象的使用具有一致性。<br>
**Component抽象构件角色**: 定义参加组合对象的共有方法和属性，可以定义一些默认的行为或属性<br>
**Leaf叶子构件**: 叶子对象，其下面没有其他分之，也就是遍历的最小单位<br>
**Composite树枝构件**: 树枝对象，作用是组合树枝节点和叶子节点形成一棵树形结构。<br>
其实就是不停滴继承上一层，然后通过将叶子放到树枝，树枝放到根，然后通过遍历链表得出，得出所有的节点信息。<br>
所以这个并不是面向接口编程，而是面向了实现类编程！不建议使用。与依赖倒置原则冲突。<br>
**场景**: 部分整体关系，例如文件夹管理，树形菜单等<br
## 装饰模式 毛坯不好看？装饰一下呗
动态地给一个对象添加一些额外的职责。就增加功能来说，装饰模式相比生成子类更为灵活。<br>
装饰模式是对继承的有力补充，用装饰模式替代即成，可以解决我们的类膨胀的问题。<br>
缺点：比较多层，像洋葱一样多，不到里面不知道里面有🐛。<br>
## 门面模式 一种让人看起来比较美
要求一个子系统的外部与其内部的通信必须通过一个同一的对象进行。门面模式提供一个高层次的接口，使得子系统更易于使用。<br>
门面模式注重“统一对象” 提供一个访问子系统的接口，除了这个接口就不允许有任何访问子系统的行为发生。<br>
提供给你一个服务，我说完，你服务就自己做，多复杂我也不知道。<br>
优点: 
* 减少系统的相互依赖<br>
* 提高了灵活性
* 提高安全性<br>
但是，不符合开闭原则。内部比较复杂，你必须修改类。<br>
**门面模式需要谨慎使用！**<br>
#### 一个子系统可以有多个门面
按照功能拆分门面，也是可以的，例如数据库的增删查改<br>
#### 门面不参与子系统内的业务逻辑
接口就是接口，要该业务逻辑就到子系统里面改。<br>

## 享元模式 我有一个池，有就拿，没就建
使用共享对象可以有效地支持大量的细粒度对象。<br>
**细粒度的对象和共享对象**<br>
共享技术：
* 内部状态<br>
内部状态是对象可共享出来的信息，存储在享元对象内部并且不会随环境改变而改变。
* 外部状态<br>
外部状态是对象得以依赖的一个标记，是随环境改变而改变的、不可以共享的状态。<br>
看一下几个角色
* 抽象享元角色<br>
就是一个产品的抽象类，同时定义出对象的外部状态和内部状态的接口或实现。
* 具体享元角色<br>
具体的一个产品类，实现抽象角色定义的业务。该角色需要注意的是内部状态处理应该与环境无关，不应该出现一个操作改变了内部状态，同时修改了外部状态。
* 不可共享的享元角色<br>
不存在外部状态或安全要求（如线程安全）不能够使用共享技术的对象，该对象一般不会出现在享元工厂中
* 享元工厂<br>
构造一个池容器，同时提供池中获得对象的方法。
```cpp
class FlyWight{//抽象享元角色
    string insidestatus;
    protected:
        string outsidestatus;
    public:
        FlyWight(string _outsidestatus){
           outsidestatus =  _outsidestatus;
        }
        operator()
        getInsidestatus(){
            return insidestatus;
        }
        setInsidestatus(){};
};
class concreteFlyWight:public FlyWight{
    public:
        concreteFlyWight(string _outsidestatus):FlyWight(_outsidestatus){
        }
        operator();
};
// 工厂
class FlyWightFactory{
    Map<string,FlyWight> pool = new Map<>();
    FlyWight getFlyWight();
}
```
优缺点：大大减少应用程序创建对象，降低程序内存的占用。增强了程序的性能，但是同时也提高了系统的复杂性，需要分离出内部状态和外部状态，而外部状态具有固化特性，不应该随内部状态改变而改变，否则导致系统内置混乱。<br>
多线程向一个池访问，减少对象的创建。<br>

## 代理模式 我有经纪人
为其他对象提供一种代理以控制对这个对象的访问。<br>
不要问我，问我的代理吧。
```cpp
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
    IGamePlayer *gameplayer; // 这个是重点！
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
```