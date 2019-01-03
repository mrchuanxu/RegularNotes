/***
 * 命令模式
 * 将一个请求封装成一个对象，从而让你使用不同的请求把客户端参数化
 * 对请求排队或者记录请求日志，可以提供命令的撤销和恢复功能
 * ***/

// 先抽象一个group
class Group{
    public:
        virtual void findGroup() = 0;
        virtual void addFeature() = 0;
        virtual void deleteFeature()= 0;
        virtual void changeFeature() = 0;
        virtual void plan() = 0;
};

class RequirementGroup:public Group{
    public:
        virtual void findGroup();
        virtual void addFeature();
        virtual void deleteFeature();
        virtual void changeFeature();
        virtual void plan();
};

class PageGroup:public Group{
    public:
        virtual void findGroup();
        virtual void addFeature();
        virtual void deleteFeature();
        virtual void changeFeature();
        virtual void plan();

};

class CodeGroup:public Group{
    public:
        virtual void findGroup();
        virtual void addFeature();
        virtual void deleteFeature();
        virtual void changeFeature();
        virtual void plan();

};

// 这时我需要抽象一个命令类，拿上面的下来用
class Command{
    protected:
        RequirementGroup *rg = new RequirementGroup();
        PageGroup *pg = new PageGroup();
        CodeGroup *cg = new CodeGroup();
    public:
        virtual void execute();
};

// 继承命令
class AddRequirementCommand:public Command{
    public:
        virtual void execute() override{ // 执行命令
            Command::cg->findGroup();
            Command::rg->findGroup();
        }
};

// 负责人invoker
class Invoker{
    private:
        Command *command;
    public:
        void setCommand(Command *refcommand){
            command = refcommand;
        }

        void action(){
            command->execute();
        }
};

int main(){
    Invoker *trans = new Invoker();
    Command *command=new AddRequirementCommand();
    trans->setCommand(command);
    trans->action(); 
    return 0;
}
