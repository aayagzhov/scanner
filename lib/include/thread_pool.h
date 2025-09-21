#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>
#include <mutex>
#include <type_traits>

namespace scanner {

class ThreadPool {
public:
    explicit ThreadPool();

    template<class F, class... Args>
    auto add_task(F&& f, Args&&... args)
            -> std::future<typename std::invoke_result<F, Args...>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mtx);

            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    };

    size_t size() {
        return tasks.size();
    }

    ~ThreadPool();

private:
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;

    std::mutex mtx;
    std::condition_variable condition;
    bool stop{false};
};

} // namespace scanner
