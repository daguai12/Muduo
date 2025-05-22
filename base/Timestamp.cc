#include "Timestamp.h"
#include <cstdio>
#include <ctime>

Timestamp::Timestamp()
{}

Timestamp::Timestamp(int64_t microSecondsSinceEpochArg)
:microSecondsSinceEpoch_(microSecondsSinceEpochArg)
{
}

Timestamp Timestamp::now()
{
    return Timestamp(time(nullptr));
}

std::string Timestamp::toString() const
{
    time_t now = time(nullptr);
    struct tm* local_time = localtime(&now);
    char buf[1024] = {0};
    snprintf(buf, 1024
             , "%4d/%02d/%02d %02d:%02d:%02d"
             ,local_time->tm_year + 1900
             ,local_time->tm_mon + 1
             ,local_time->tm_mday
             ,local_time->tm_hour
             ,local_time->tm_min
             ,local_time->tm_sec);
    return buf;
}



