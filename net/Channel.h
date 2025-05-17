#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H
#include <functional>
#include <memory>
#include "Timestamp.h"
#include "EventLoop.h"
#include "nocopyable.h"


class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>; 
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop* loop,int fd);
    ~Channel();

    void handleEvent(Timestamp receiveTime);
    // 对外接口设置回掉函数
    void setReadCallback(ReadEventCallback cb)
    {readCallback_ = std::move(cb);}
    void setWriteCallback(EventCallback cb)
    {writeCallback_ = std::move(cb);}
    void setCloseCallback(EventCallback cb)
    {closeCallback_ = std::move(cb);}
    void setErrorCallback(EventCallback cb)
    {errorCallback_ = std::move(cb);}

    // 防止回调执行过程中对象被销毁
    void tie(const std::shared_ptr<void>&);

    int fd() const {return fd_;}
    int events() const {return events_;}
    void set_revents(int revt) { revents_ = revt;}

    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }

    bool isNonEvent() const { return events_ == kNoneEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isReading() const { return events_ & kReadEvent; }

    //for Poller
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    //for loop
    EventLoop* ownerLoop() {return loop_;}
    void remove();
private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);

    // 设置事件类型
    static const int kNoneEvent; //没有事件发生
    static const int kReadEvent; //读事件发生
    static const int kWriteEvent; //写事件发生

    EventLoop* loop_;
    const int fd_; // Channel所监听的fd
    int events_; // fd_所监听的事件集合
    int revents_; // 返回已经就绪的事件集合
    int index_; 

    std::weak_ptr<void> tie_;
    bool tied_;
    
    // fd对应事件触发时，所调用的回掉函数
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};
#endif
