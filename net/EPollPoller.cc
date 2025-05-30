#include "EPollPoller.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Timestamp.h"
#include "Logger.h"
#include <sys/epoll.h>
#include <strings.h>
#include <unistd.h>

const int kNew = -1;
const int kAdded = 1; 
const int kDeleted = 2;

EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize)
{
    if(epollfd_ < 0)
    {

    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
    LOG_ERROR("func=%s => fd total count:%lu \n",__FUNCTION__,channels_.size());
    int numEvents = ::epoll_wait(epollfd_, 
                                 &*events_.begin(), 
                                 static_cast<int>(events_.size()), 
                                 timeoutMs);
    int saveErrno = errno; //保存全局变量errno，保证函数的可冲入性
    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        fillActiveChannels(numEvents, activeChannels);
        if (numEvents == events_.size())
        {
            events_.resize(2*events_.size());
        }
    }
    else if (numEvents == 0)
    {
        LOG_DEBUG("%s timeout!\n",__FUNCTION__);
    }
    else
    {
        if (saveErrno != EINTR)
        {
            errno = saveErrno;
            LOG_ERROR("EPollPoller::poll() err!");
        }
    }
    return now;
}

void EPollPoller::updateChannel(Channel* channel)
{
    const int index = channel->index(); 
    LOG_DEBUG("func=%s => fd=%d events=%d index=%d \n",__FUNCTION__,channel->fd(),channel->events(),channel->index());

    if (index == kNew || index == kDeleted)
    {
        if (index == kNew)
        {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
    }
    else
    {
        int fd = channel->fd();
        if (channel->isNonEvent())
        {
            update(EPOLL_CTL_DEL,channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD,channel);
        }
    }
}

void EPollPoller::removeChannel(Channel* channel)
{
    int fd = channel->fd();
    channels_.erase(fd);

    LOG_DEBUG("func%s => fd=%d\n", __FUNCTION__, fd);

    int index = channel->index();
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}



void EPollPoller::fillActiveChannels(int numEvents,
                            ChannelList* activeChannels) const
{
    for (int i = 0;i < numEvents; ++i)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

void EPollPoller::update(int operation,Channel* channel)
{
    epoll_event event;
    bzero(&event, sizeof event);

    int fd = channel->fd();
    event.events = channel->events();
    // event.data.fd = fd;
    event.data.ptr = channel;

    if (::epoll_ctl(epollfd_,operation,fd,&event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll_ctl del error:%d\n",errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/mod error:%d\n",errno);
        }
    }

}
