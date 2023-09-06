#pragma once

#include <iostream>
#include <mutex>
#include <list>
#include <thread>

std::list<int> myList;
std::mutex m;

using namespace std;

void insert(int const &x)
{
    lock_guard<mutex> lg(m);
    myList.push_front(x);
}

void size()
{
    m.lock();
    int size = myList.size();
    m.unlock();
    cout << "size of the list is : " << size << endl;
}

void run()
{
    thread thread1(insert, 4);
    thread thread2(insert, 11);

    thread1.join();
    thread2.join();
}