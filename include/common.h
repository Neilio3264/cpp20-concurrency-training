#pragma once

#include <thread>

class ThreadGuard
{
public:
    // Create explicit constructor as we don't want any implicit conversions
    // such as comparision where one object can be implied to be another
    // data type
    explicit ThreadGuard(std::thread &_t) : t(_t)
    {
    }

    // If this object is not already joined or detached, then
    // call join() before before object is deleted at execution end
    ~ThreadGuard()
    {
        if (t.joinable())
            t.join();
    }

    // We do not want this class to have the ability to copy
    // delete copy operator and copy constructor
    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard &operator=(const ThreadGuard &) = delete;

private:
    std::thread &t;
};