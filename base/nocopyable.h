#ifndef MUDUO_BASE_NOCOPYABLE_H
#define MUDUO_BASE_NOCOPYABLE_H

/*
    继承该类的子类不可以被拷贝，但可以调用构造函数和析构函数
*/
class noncopyable
{
public:
    noncopyable(noncopyable& ) = delete;
    noncopyable& operator=(noncopyable& ) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif

