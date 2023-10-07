#pragma once

// Implement a queue data structure using linked list
// Make it thread safe
// Allows true concurrency with multiple mutex

// * Make use of a dummy node that tail always points to
// * Used to avoid edge case race condition

#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

template <typename T>
class sequentialQueue
{
private:
    struct node
    {
        shared_ptr<T> data;
        unique_ptr<node> next;

        node() {}
        node(T _data) : data(move(_data)) {}
    };

    unique_ptr<node> head;
    node *tail;
    mutex head_mut;
    mutex tail_mut;
    condition_variable cv;

    node *getTail()
    {
        lock_guard<mutex> tLock(tail_mut);
        return tail;
    }

    unique_ptr<node> waitPopHead()
    {
    }

public:
    sequentialQueue() : head(new node), tail(head.get()) {}

    void push(T value)
    {
        shared_ptr<T> newData(make_shared<T>(move(value)));
        unique_ptr<node> dummy(new node);
        node *newTail = dummy.get();
        {
            lock_guard<mutex> tLock(tail_mut);
            tail->data = newData;
            tail->next = move(dummy);
            tail = newTail;
        }

        cv.notify_one();
    }

    shared_ptr<T> pop()
    {
        lock_guard<mutex> hLock(head_mut);
        if (head.get() == getTail())
            return shared_ptr<T>();

        shared_ptr<T> res(head->data);
        unique_ptr<node> oldHead = move(head);
        head = move(oldHead->next);
        return res;
    }

    void printData();
};

template <typename T>
inline void sequentialQueue<T>::printData()
{
    if (head.get() == getTail())
    {
        cout << "Queue is empty...\n";
        return;
    }

    lock_guard<mutex> hLock(head_mut);

    node *current = head.get();
    cout << "Queue from top to bottom...\n";
    int index{};
    while (current->data != nullptr)
    {
        cout << "current: " << current << ", value [" << index++ << "]: " << *(current->data) << endl;
        current = (current->next).get();
    }
    std::cout << "End of the queue...\n";
}