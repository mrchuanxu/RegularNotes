/***
 * 模拟一个shell用户登陆程序
 * ***/
#include <stdio.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    char name[32] = "",*pwd;
    struct spwd *p;
    size_t namelen = 0;

    printf("enter username: ");
    fgets(name,32,stdin);
    pwd = getpass("enter pass:"); // 获得密码的输入key

    namelen = strlen(name);
    name[namelen-1] = 0;
    p = getspnam(name); // 访问shadow文件，获得加密的密文
    if(!p){
        fprintf(srderr,"error user or pass");
        return -1;
    }

    if(!strcmp(crypt(pwd,p->sp_pwdp),p->sp_pwdp)){
        printf("pass correct");
    }else{
        fprintf(stderr,"err user or pass");
    }
    return 0;
}
