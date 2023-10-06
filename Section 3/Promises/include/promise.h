#pragma once

#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <math.h>

using namespace std;

void throwException()
{
    throw invalid_argument("input cannot be negative");
}

void calculate(promise<int> &prom)
{
    int x = 1;
    cout << "Please, enter an integer value: ";
    try
    {
        cin >> x;
        if (x < 0)
            throwException();
        prom.set_value(sqrt(x));
    }
    catch (const std::exception &e)
    {
        prom.set_exception(current_exception());
    }
}

void printResult(future<int> &fut)
{
    try
    {
        int x = fut.get();
        cout << "value: " << x << '\n';
    }
    catch (exception &e)
    {
        cout << "[EXCEPTION CAUGHT: " << e.what() << "]\n";
    }
}

void print(future<int> &fut)
{
    cout << "Waiting for value in print thread \n";
    cout << "value: " << fut.get() << endl;
}

void run()
{
    promise<int> prom;
    future<int> fut = prom.get_future();

    thread printThread(print, ref(fut));

    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "Setting the value in main thread \n";
    prom.set_value(10);

    printThread.join();
    // ! Be aware of potential deadlock here if you set promise value after join()
    // ! The join() will wait until print is done and print will wait until value is updated

    promise<int> ise;
    future<int> ure = ise.get_future();
    thread printResultThread(printResult, ref(ure));
    thread calculationThread(calculate, ref(ise));

    printResultThread.join();
    calculationThread.join();
}