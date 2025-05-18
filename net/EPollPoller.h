#ifndef MUDUO_NET_EPOLLPOLLER_H
#define MUDUO_NET_EPOLLPOLLER_H

#include "EventLoop.h"
#include "Poller.h"
#include "Timestamp.h"
#include <vector>
#include <sys/epoll.h>

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop* loop);
    ~EPollPoller() override;

    Timestamp poll(int timeoutMs,ChannelList* activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channel) override;
private:
    static const int kInitEventListSize = 16; //就绪队列的大小
    
    void fillActiveChannels(int numEvents,
                            ChannelList* activeChannels) const;

    void update(int operation,Channel* channel);
    using EventList = std::vector<epoll_event>;

    int epollfd_; // 保存内核数据结构的句柄(epfd)
    EventList events_; // 就绪队列
};
#endif

