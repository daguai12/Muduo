#include "CurrentThread.h"
#include <sys/syscall.h>
#include <unistd.h>

__thread int t_cacheTid = 0;

void CurrentThread::cacheTid()
{
    if (t_cacheTid == 0)
    {
        t_cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
    }
}

