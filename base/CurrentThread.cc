#include "CurrentThread.h"
#include <sys/syscall.h>
#include <unistd.h>

namespace CurrentThread
{
__thread int t_cachedTid = 0;
}

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
    }
}
