#pragma once

#include <iostream>
#include "common.h"

using namespace std;

void functionTwo(int &x)
{
    while (true)
    {
        try
        {
            cout << x << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
            throw runtime_error("Runtime Error");
        }
    }
}

// ! When functionOne finishes execution, it will destruct
// ! object in reverse order. Since Thread 2 is detached,
// ! once Thread 1 is finished, no destructor will ever be called
// ! Thread 2.
// ? Thread 2 runs independent thus it continues to access the object
// ? memory since x is passed by reference. The memory does not
// ? exist and thus throws an exception
// * Be careful with detached threads as threads can outlive
// * the live of variables or other threads.
void functionOne()
{
    int x = 5;
    thread threadTwo(functionTwo, ref(x));
    threadTwo.detach();
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Thread 1 Finished Execution" << endl;
}

void run()
{
    thread threadOne(functionOne);
    threadOne.join();
}