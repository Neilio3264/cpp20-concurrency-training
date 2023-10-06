#pragma once

#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <mutex>

using namespace std;

void printResult(std::future<int> &fut)
{
    cout << fut.get() << endl;
}

void run()
{
    promise<int> prom;
    future<int> fut(prom.get_future());

    thread th1(printResult, ref(fut));
    thread th2(printResult, ref(fut));

    prom.set_value(5);

    th1.join();
    th2.join();
}