#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static sigjmp_buf env;

static void fun(void){
    long long i = 0;
    sigsetjmp(env,1); // jmp的位置
    printf("before %s\n",__FUNCTION__);
    for(i = 0;i<1000000000;i++);
    printf("end%s\n",__FUNCTION__);
}

static void a_handler(int s){
    printf("before %s\n",__FUNCTION__);
    siglongjmp(env,1); // 这里恢复了信号
    printf("end%s\n",__FUNCTION__);
}

int main(void){
    long long i=0;
    struct sigaction sa;
    // 改用sigaction
    sa.sa_handler = a_handler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGINT);
    // 任意信号想要杀死进程，把资源释放掉再结束即可
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);
    fun();

for(i = 0;;i++){
    printf("%lld\n",i);
    pause(); // 等待信号打断等待 
}
}