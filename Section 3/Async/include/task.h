#pragma once

#include <iostream>
#include <thread>
#include <future>

using namespace std;

void printing()
{
    cout << "Printing running on - " << this_thread::get_id() << endl;
}

int addition(int x, int y)
{
    cout << "Addition running on - " << this_thread::get_id() << endl;
    return x + y;
}

int subtraction(int x, int y)
{
    cout << "Subtraction running on - " << this_thread::get_id() << endl;
    return x - y;
}

void task()
{
    cout << "Main Thread ID - " << this_thread::get_id() << endl;

    int x = 100;
    int y = 50;

    future<void> f1 = async(launch::async, printing);
    future<int> f2 = async(launch::deferred, addition, x, y);
    future<int> f3 = async(launch::deferred | launch::async, subtraction, x, y);

    f1.get();
    cout << "Value received using f2 future - " << f2.get() << endl;
    cout << "Value received using f3 future - " << f3.get() << endl;
}