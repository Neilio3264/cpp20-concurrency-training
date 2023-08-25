#pragma once

#include <iostream>
#include <thread>

using namespace std;

void test()
{
    cout << "Hello from test" << endl;
}

void run()
{
    // Here, thread1 launches and executes test
    // Immediately represents an active thread of execution
    // thread1 now at joinable state
    thread thread1(test);

    if (thread1.joinable())
    {
        cout << "Thread 1 is joinable before join() call" << endl;
    }
    else
    {
        cout << "Thread 1 is not joinable before join() call" << endl;
    }

    // No join or detach leads to exception
    thread1.join();

    if (thread1.joinable())
    {
        cout << "Thread 1 is joinable after join() call" << endl;
    }
    else
    {
        cout << "Thread 1 is not joinable after join() call" << endl;
    }

    // thread1.join();
    // Leads to exception as join or detach can only be called once
    // once in a threads lifecycle

    // Default constructor thread
    // Not a properly constructed thread
    thread thread2;

    // Default constructed thread does not represent any active thread
    // of execution -> non-joinable
    if (thread2.joinable())
    {
        cout << "Thread 2 is joinable before join() call" << endl;
    }
    else
    {
        cout << "Thread 2 is not joinable before join() call" << endl;
    }
}