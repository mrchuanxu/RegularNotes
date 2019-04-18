#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <thread> // 加线程操作库
#include <mutex> // 加锁库
#include <atomic> // 加原子操作
#include <condition_variable> // 加条件变量
#include <functional> // 加function操作
#include <future>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace mythreadpool{
    class ThreadsGuard{
        public:
            ThreadsGuard(std::vector<std::thread>&v):threads_(v){}
            ~ThreadsGuard(){
                for(size_t i=0;i!=threads_.size();++i){
                    if(threads_[i].joinable()){
                        threads_[i].join();
                    }
                }
            }
        private:
        ThreadsGuard(ThreadsGuard&&) = delete;
        ThreadsGuard& operator=(ThreadsGuard&& tg) = delete;
        ThreadsGuard(const ThreadsGuard&) = delete;
        ThreadsGuard& operator=(const ThreadsGuard&) = delete;
        private:
        std::vector<std::thread> threads_;
    };

    class ThreadPool{
        public:
        typedef std::function<void()> task_type;
        public:
            explicit ThreadPool(int n = 0);
            ~ThreadPool(){
                stop();
                cond_.notify_all();
            }
            void stop(){
                stop_.store(true,std::memory_order_release);
            }
            template<class Function,class ... Args>
            std::future<typename std::result_of<Function(Args...)>::type> add(Function&&,Args&&...);
        private:
        ThreadPool(ThreadPool&&) = delete;
        ThreadPool& operator=(ThreadPool&&) = delete;
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&)=delete;
        std::atomic<bool> stop_;
        std::mutex mtx_;
        std::condition_variable cond_;

        std::queue<task_type> tasks_;
        std::vector<std::thread> threads_;
        mythreadpool::ThreadsGuard tg_;
    };
}

#endif // !THREAD_POOL_H