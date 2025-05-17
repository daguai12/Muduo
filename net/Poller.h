#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H
#include "EventLoop.h"
#include "Timestamp.h"
#include "nocopyable.h"
#include <unordered_map>
#include <vector>

class EventLoop;
class Channel;

class Poller : noncopyable
{
public:
    // 存储活跃的 Channel* 指针表
    using ChannelList = std::vector<Channel*>;
    // 绑定Poller所属的EventLoop
    Poller(EventLoop* loop);
    virtual ~Poller();

    virtual Timestamp poll(int timeoutMs,ChannelList* activeChannels) = 0;
    
    // 修改channel所监听的事件
    virtual void updateChannel(Channel* channel) = 0;
    // 移除channel所监听的事件
    virtual void removeChannel(Channel* channel) = 0;

    // 判断参数中的channel是否在当前Poller中
    bool hasChannel(Channel* channel) const;
    
    // 返回默认的Poller实现
    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    // key: fd  value: Channel* 
    using ChannelMap = std::unordered_map<int,Channel*>;
    ChannelMap channels_;
private:
    // 当前Poller绑定的EventLoop
    EventLoop* ownerLoop_;
};
#endif
