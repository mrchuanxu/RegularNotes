#include <stdio.h>
#include <time.h>

int main(void){
    long long count = 0;
    time_t t;
    t = time(NULL)+5; // 延迟5秒
    while(time(NULL)<t){
        count++;
    }
    printf("%lld\n",count);
    return 0;
}