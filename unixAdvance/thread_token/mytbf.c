#include "../include/apue.h"
#include <fcntl.h>
#include <pthread.h>

#include "mytbf.h"

// 每个令牌桶
struct mytbf_st{
    int cps; // 速率
    int burst; // 令牌上限
    int token; // 可用令牌数量
    int pos; // 当前令牌桶在job 数组中的下标
    pthread_mutex_t mut; // 用来保护令牌竞争的互斥量
};

// 所有的令牌桶
static struct mytbf_st *job[MYTBF_MAX];
// 用来保护令牌桶数组竞争的互斥量
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
// 添加令牌的线程ID
static pthread_t tid;
// 初始化添加令牌的线程
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

// 线程处理函数：负责定时向令牌桶中添加令牌
static void *thr_alrm(void *p){
    int i;
    while(1){
        pthread_mutex_lock(&mut_job);
        // 遍历所有桶
        for(i = 0;i<MYTBF_MAX;i++){
            // 为可用的桶添加令牌
            if(job[i]!=NULL){
                pthread_mutex_lock(&job[i]->mut);
                job[i]->token += job[i]->cps;
                // 控制桶中可用的令牌不能超过上限
                if(job[i]->token > job[i]->burst)
                    job[i]->token = job[i]->burst;
                pthread_mutex_unlock(&job[i]->mut);
            }
        }
        pthread_mutex_unlock(&mut_job);// 解锁互斥量
        sleep(1);// 等待一秒钟后继续添加令牌
    }
    pthread_exit(NULL);
}
static void module_unload(void){
    int i;
    pthread_cancel(tid);
    // 终止某线程
    pthread_join(tid,NULL);
    // 等待线程终止
    pthread_mutex_lock(&mut_job);
    // 锁住互斥量
    for(i = 0;i<MYTBF_MAX;i++){// 遍历所有的桶
        if(job[i]!=NULL){
            // 销毁所有的桶
            pthread_mutex_destroy(&job[i]->mut);
            free(job[i]);
        }
    }
    pthread_mutex_unlock(&mut_job);
    pthread_mutex_destroy(&mut_job);
}

static void module_load(void){
    int err;
    // 创建线程
    err = pthread_create(&tid,NULL,thr_alrm,NULL);
    if(err){
        fprintf(stderr,"pthread_create():%s\n",strerror(err));
        exit(1);
    }
    atexit(module_unload);
}
/***
 * 为了不破坏调用者对令牌桶操作的原子性
 * 在该函数内加锁可能导致死锁
 * 所以该函数内部无法加锁
 * 必须在调用该函数之前先加锁
 * ***/
static int get_free_pos_unlocked(void){
    int i;
    for(i = 0;i<MYTBF_MAX;i++){
        if(job[i]==NULL)
            return i;
    }
    return -1;
}

mytbf_t *mytbf_init(int cps,int burst){
    struct mytbf_st *me;
    int pos;

    pthread_once(&init_once,module_load);

    me = malloc(sizeof(*me));
    if(NULL == me)
        return NULL;
    
    me->cps = cps;
    me->burst = burst;
    me->token = 0;

    pthread_mutex_init(&me->mut,NULL);

    pthread_mutex_lock(&mut_job);

    pos = get_free_pos_unlocked();
    if(pos<0){
        // 带锁跳转，先解锁再跳转
        pthread_mutex_unlock(&mut_job);
        free(me);
        return NULL;
    }

    me->pos = pos;

    job[pos] = me;

    pthread_mutex_unlock(&mut_job);

    return me;
}

static inline int min(int a,int b){
    return (a<b)?a:b;
}

int mytbf_fetchtoken(mytbf_t *ptr,int size){
    int n;
    struct mytbf_st *me = ptr;

    if(size < 0)
        return -EINVAL;
    pthread_mutex_lock(&me->mut);
    // 令牌数量不足，就等待令牌被添加进来
    while(me->token <= 0){
        pthread_mutex_unlock(&me->mut);
        sched_yield();// 作用是出让调度器
        pthread_mutex_lock(&me->mut);
    }

    n = min(me->token,size);
    me->token -= n;

    pthread_mutex_unlock(&me->mut);

    return n;
}

// 令牌用不完就归还，不能浪费
int mytbf_returntoken(mytbf_t *ptr,int size){
    struct mytbf_st *me = ptr;
    if(size < 0)
        return -EINVAL;
    pthread_mutex_lock(&me->mut);

    me->token += size;
    if(me->token > me->burst)
        me->token = me->burst;
    
    pthread_mutex_unlock(&me->mut);

    return size;
}

void mytbf_destory(mytbf_t *ptr){
    struct mytbf_st *me = ptr;

    pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_unlock(&mut_job);

    pthread_mutex_destroy(&me->mut);
    free(ptr);
}
