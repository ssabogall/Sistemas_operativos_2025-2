#pragma once
#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t n);
    void submit(std::function<void()> fn);
    void close(); // no más trabajos; join
private:
    void worker();
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> q_;
    std::mutex m_;
    std::condition_variable cv_;
    bool done_ = false;
};
