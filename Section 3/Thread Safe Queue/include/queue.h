#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>
#include <thread>

template <typename T>
class Queue
{
    std::mutex m;
    std::condition_variable cv;
    std::queue<std::shared_ptr<T>> queue;

public:
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(m);
        queue.push(std::make_shared<T>(value));
        cv.notify_one();
    }
    bool pop(T &ref)
    {
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (queue.empty())
        {
            return std::shared_ptr<T>();
        }
        else
        {
            std::shared_ptr<T> ref(queue.front());
            queue.pop();
            return ref;
        }
    }

    /**
     * @brief The function allows a thread to wait until the queue is not empty
     *        If no item is in the queue, the function will wait until the queue is populated.
     *        The thread is then notified to continue pop execution.
     *
     * @param ref
     */
    bool wait_pop(T &ref);
    std::shared_ptr<T> wait_pop()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]
                { return !queue.empty(); });
        std::shared_ptr<T> ref = queue.front();
        queue.pop();
        return ref;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m);
        return queue.empty();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(m);
        return queue.size();
    }
};
