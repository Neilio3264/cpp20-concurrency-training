#pragma once

#include <iostream>
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

void run()
{
    cout << "Main Thread ID - " << this_thread::get_id() << endl;

    int x = 100;
    int y = 50;

    future<void> f1 = async(launch::async, printing);
    future<int> f2 = async(launch::deferred, addition, x, y);

    f1.get();
    cout << "Value received using f2 future - " << f2.get() << endl;
}