#include "thread_pool.h"
ThreadPool::ThreadPool(size_t n) {
    if (n==0) n=1;
    for (size_t i=0;i<n;i++) threads_.emplace_back(&ThreadPool::worker, this);
}
void ThreadPool::submit(std::function<void()> fn) {
    { std::lock_guard<std::mutex> lk(m_); q_.push(std::move(fn)); }
    cv_.notify_one();
}
void ThreadPool::close() {
    { std::lock_guard<std::mutex> lk(m_); done_ = true; }
    cv_.notify_all();
    for (auto& t: threads_) t.join();
}
void ThreadPool::worker() {
    for (;;) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lk(m_);
            cv_.wait(lk,[&]{ return done_ || !q_.empty(); });
            if (done_ && q_.empty()) return;
            job = std::move(q_.front()); q_.pop();
        }
        job();
    }
}
