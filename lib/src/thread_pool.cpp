#include "thread_pool.h"

namespace scanner {

ThreadPool::ThreadPool() {
    size_t threads_count = std::thread::hardware_concurrency();
    for (size_t i{0}; i < threads_count; ++i) {
        threads.emplace_back([this](){
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock, [this] {return stop || !tasks.empty();});
                    if (stop && tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &thread : threads)
        thread.join();
}

} // namespace scanner
