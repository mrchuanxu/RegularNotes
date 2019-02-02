#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t condc,condp; // 条件变量
pthread_mutex_t the_mutex; // 互斥锁

unsigned int buffer = 0;
const int MAX = 100;

void *producer(void *ptr){ // 生产者
    for(int i = 1;i < MAX;i++){
        pthread_mutex_lock(&the_mutex); // 锁住资源
        while(buffer != 0) pthread_cond_wait(&condp,&the_mutex); // 对互斥量解锁
        sleep(1);
        buffer = i;
        printf("producer pthread produce one production %d.\n",i);
        // 唤醒两个消费者线程
        pthread_cond_broadcast(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0); // 退出线程
}

void *consumer1(void *ptr){
    for(int i = 1;i<MAX;i++){
        pthread_mutex_lock(&the_mutex); //  共用一个锁，锁住同一个资源
        while(buffer == 0) pthread_cond_wait(&condc,&the_mutex); // 这是上面传下来的条件变量
        printf("consumer1 pthread consume one production %d\n",buffer);
        buffer = 0;
        pthread_cond_signal(&condp); // 通知线程 条件已经满足
        pthread_mutex_unlock(&the_mutex); // 解锁资源
    }
    pthread_exit(0);
}

void *consumer2(void *ptr){
    for(int i = 1;i<MAX;i++){
        pthread_mutex_lock(&the_mutex); //  共用一个锁，锁住同一个资源
        while(buffer == 0) pthread_cond_wait(&condc,&the_mutex); // 这是上面传下来的条件变量
        printf("consumer2 pthread consume one production %d\n",buffer);
        buffer = 0;
        pthread_cond_signal(&condp); // 通知线程 条件已经满足
        pthread_mutex_unlock(&the_mutex); // 解锁资源
    }
    pthread_exit(0);
}

int main(void){
    pthread_t pro,con1,con2;
    pthread_mutex_init(&the_mutex,0); // 初始化锁，0
    pthread_cond_init(&condc,0);
    pthread_cond_init(&condp,0); // 这时候就需要讲讲线程的创建了
    pthread_create(&con1,0,consumer1,0);
    pthread_create(&pro,0,producer,0);
    pthread_create(&con2,0,consumer2,0);
    pthread_join(pro, 0);
    pthread_join(con1, 0);
    pthread_join(con2, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
    return 0;
}