/**
 * @file thread_pool.h
 * @brief Thread pool implementation for concurrent task execution
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file contains a thread pool class that manages a pool of worker threads
 * and a task queue. Tasks are added to the queue and executed by available threads.
 * The implementation uses C++11 threading primitives for synchronization.
 */
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

/**
 * @class ThreadPool
 * @brief A thread pool for managing and executing concurrent tasks
 * 
 * @details
 * The ThreadPool class maintains a fixed number of worker threads that continuously
 * wait for tasks to be added to a queue. Tasks are executed in the order they are
 * added (FIFO). The class provides thread-safe task submission and supports
 * getting futures for task results.
 */
class ThreadPool {
public:
    /**
     * @brief Constructs a thread pool with hardware concurrency number of threads
     */
    explicit ThreadPool();

    /**
     * @brief Adds a task to the thread pool
     * @tparam F Callable type (function, lambda, etc.)
     * @tparam Args Types of arguments to pass to the callable
     * @param f Callable object to execute
     * @param args Arguments to forward to the callable
     * @return std::future containing the result of the task
     * @throws std::runtime_error if called on stopped ThreadPool
     * 
     * @details
     * This method templates the function and its arguments, creates a packaged_task,
     * and returns a future for the result. The task is added to the queue and
     * will be executed by an available worker thread.
     */
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

    /**
     * @brief Destructor - stops all threads and waits for completion
     */
    ~ThreadPool();

private:
    std::queue<std::function<void()>> tasks;  ///< Queue of pending tasks
    std::vector<std::thread> threads;         ///< Worker threads

    std::mutex mtx;                           ///< Mutex for synchronizing access to tasks queue
    std::condition_variable condition;        ///< Condition variable for thread notification
    bool stop{false};                         ///< Flag indicating whether pool should stop
};

} // namespace scanner
