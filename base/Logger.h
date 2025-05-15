#ifndef MUDUO_BASE_LOGGER_H
#define MUDUO_BASE_LOGGER_H

#include <string>
#include <cstdlib>
#include "nocopyable.h"

// LOG_INFO("%s %d",arg1,arg2)
#define LOG_INFO(logmsgFormat, ...)                     \
do {                                                \
    Logger &logger = Logger::instance();            \
    logger.setLogLevel(INFO);                    \
    char buf[1024] = {0};                           \
    snprintf(buf, sizeof(buf), logmsgFormat, ##__VA_ARGS__); \
    logger.log(buf);                                \
} while(0)

#define LOG_ERROR(logmsgFormat,...)\
do{ \
    Logger &logger = Logger::instance(); \
    logger.setLogLevel(ERROR); \
    char buf[1024] = {0}; \
    snprintf(buf,1024, logmsgFormat,##__VA_ARGS__); \
    logger.log(buf); \
}while(0) \

#define LOG_DEBUG(logmsgFormat,...)\
do{ \
    Logger &logger = Logger::instance(); \
    logger.setLogLevel(DEBUG); \
    char buf[1024] = {0}; \
    snprintf(buf,1024, logmsgFormat,##__VA_ARGS__); \
    logger.log(buf); \
}while(0) \

#define LOG_FATAL(logmsgFormat,...)\
do{ \
    Logger &logger = Logger::instance(); \
    logger.setLogLevel(FATAL); \
    char buf[1024] = {0}; \
    snprintf(buf,1024, logmsgFormat,##__VA_ARGS__); \
    logger.log(buf); \
}while(0) \

enum LogLevel
{
    INFO,
    ERROR,
    DEBUG,
    FATAL
};

class Logger : noncopyable
{
public:
    //获取日志的唯一实例对象
    static Logger& instance();
    //设置日志的级别
    void setLogLevel(int logLevel);
    //写日志
    void log(const std::string& msg);
private:
    int LogLevel_;
    Logger(){}
};

#endif //MYMUDUO_BASE_LOGING_H
