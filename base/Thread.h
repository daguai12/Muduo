#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include <functional>
#include <atomic>
#include <string>
#include <memory>
#include <thread>
#include "nocopyable.h"

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc,const std::string& name = std::string());

    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_; }
private:
    void setDefaultName();

    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    ThreadFunc func_;
    pid_t tid_;
    std::string name_;
    static std::atomic_int32_t numCreated_;
};

#endif
