#ifndef MUDUO_NET_INETADDRESS_H
#define MUDUO_NET_INETADDRESS_H

#include <cstdint>
#include <arpa/inet.h>
#include <string>
#include "copyable.h"

class InetAddress : public copyable
{
public:
    explicit InetAddress(std::string ip = "127.0.0.1",uint16_t port = 6000);
    explicit InetAddress(const struct sockaddr_in& addr)
    :addr_(addr)
    {}
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const struct sockaddr_in* getSockAddr() const
    {return &addr_;}
private:
    struct sockaddr_in addr_;
};
#endif
