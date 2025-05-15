#include <iostream>
#include <assert.h>
#include "InetAddress.h"

int main()
{
    InetAddress addr;
    std::cout << addr.toIp();
    
    // 检查 IP
    assert(addr.toIp() == "127.0.0.1");
    std::cout << "toIp() OK" << std::endl;

    // 检查端口
    assert(addr.toPort() == 6000);
    std::cout << "toPort() OK" << std::endl;

    // 检查 IP:Port
    assert(addr.toIpPort() == "127.0.0.1:6000");
    std::cout << "toIpPort() OK" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;

}
