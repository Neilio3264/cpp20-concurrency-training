#pragma once

#include <atomic>
#include <iostream>
#include "common.h"

thread_local std::atomic<int> i;

using namespace std;

void foo()
{
    ++i;
    cout << i;
}

void run()
{
    thread thread1(foo);
    thread thread2(foo);
    thread thread3(foo);

    thread1.join();
    thread2.join();
    thread3.join();

    cout << endl;
}