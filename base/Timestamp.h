#ifndef MUDUO_BASE_TIMESTAMP
#define MUDUO_BASE_TIMESTAMP

#include <cstdint>
#include <string>
#include <ctime>

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpochArg);
    static Timestamp now();
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};

#endif

