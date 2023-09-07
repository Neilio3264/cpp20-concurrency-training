#pragma once

#include <iostream>
#include <mutex>
#include <stack>
#include <thread>
#include <memory>
#include <stdexcept>

template <typename T>
class tsStack
{
private:
    std::stack<std::shared_ptr<T>> stk;
    std::mutex m;

public:
    void push(T element)
    {
        std::lock_guard<std::mutex> lock(m);
        stk.push(std::make_shared<T>(element));
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (stk.empty())
            throw std::runtime_error("stack is empty");

        std::shared_ptr<T> res(stk.top());
        stk.pop();
        return res;
    }

    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (stk.empty())
            throw std::runtime_error("stack is empty");

        value = *(stk.top().get());
        stk.pop();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m);
        return stk.empty();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(m);
        return stk.size();
    }
};