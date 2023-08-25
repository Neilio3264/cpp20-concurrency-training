#pragma once

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void foo()
{
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "Hello from foo" << endl;
}

void bar()
{
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "Hello from bar" << endl;
}

void run()
{
    thread fooThread(foo);
    thread barThread(bar);

    // Detach does not block main thread execution
    // The thread that is detached is allowed to complete execution
    // independent of the main thread that launched it
    barThread.detach();
    // This print executes before bar thread is complete as bar thread
    // is in a sleep state for 5 seconds
    cout << "This is after bar thread detach" << endl;

    // Join gives threads syncronization with its main/parent thread
    // Main execution is paused until the thread that calls join is complete
    fooThread.join();
    cout << "This is after foo thread join" << endl;
}