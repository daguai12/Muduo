#include <iostream>
#include "Logger.h"
#include "Timestamp.h"

//获取日志的唯一实例对象
Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

//设置日志的级别
void Logger::setLogLevel(int logLevel)
{
    this->LogLevel_ = logLevel;
}

//写日志
void Logger::log(const std::string& msg)
{
    switch (LogLevel_) 
    {
        case(INFO)
            : std::cout << "[INFO]";
        break;
        case(ERROR)
            : std::cout << "[ERROR]";
        break;
        case(DEBUG)
            : std::cout << "[DEBUG]";
        break;
        case(FATAL)
            : std::cout << "[FATAL]";
        break;
        default:
        break;
    }

    std::cout << " " << Timestamp::now().toString() <<  " : " << msg << std::endl;
}

