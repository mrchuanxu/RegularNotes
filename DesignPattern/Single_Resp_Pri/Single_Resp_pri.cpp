#include <iostream>
#include <string>

using namespace std;
// 两个接口 实现
class IUserBo{
    public:
        IUserBo() = default;
        virtual ~IUserBo();
        virtual void setUserID();
        virtual void setPassword(char *password);
        virtual void getPassword();
        virtual void setUserName(string &username);
        virtual string& getUserName();
};

class IUserBiz{
    public:
        IUserBiz() = default;
        virtual ~IUserBiz();
        virtual bool changePassword();
        virtual bool deleteUser(IUserBo &userBo);
        virtual bool addOrg(IUserBo &userBo);
        virtual bool addRole(IUserBo &userBo);
};

class IUserInfo:private IUserBiz,private IUserBo{
    public:
        IUserInfo() = default;
        void setUserID() override;
        void setPassword(char *password) override;
        bool changePassword() override;
        void getPassword() override;
    private:
        char* Password;
};

void IUserInfo::setPassword(char *password){
    Password = password;
}

void IUserInfo::getPassword(){
    cout << *Password << endl;
}

int main(int agrc,char* argv[]){
    IUserInfo *userInfo = new IUserInfo();
    userInfo->setPassword(argv[1]);
    userInfo->getPassword();
    return 0;
}