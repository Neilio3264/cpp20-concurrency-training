#pragma once

#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <stdexcept>

using namespace std;

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
}