#pragma once

#include <iostream>
#include <mutex>
#include <stack>
#include <thread>

// ! Notice this implementation still has race conditions
// ! inherent from the interface
template <typename T>
class tsStack
{
private:
    std::stack<T> stk;
    std::mutex m;

public:
    tsStack();
    ~tsStack();

    void push(T element)
    {
        std::lock_guard<std::mutex> lock(m);
        stk.push(element);
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(m);
        stk.pop();
    }

    T &top()
    {
        std::lock_guard<std::mutex> lock(m);
        return stk.top();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m);
        return stk.empty();
    }

    int size()
    {
        std::lock_guard<std::mutex> lock(m);
        return stk.size();
    }
};