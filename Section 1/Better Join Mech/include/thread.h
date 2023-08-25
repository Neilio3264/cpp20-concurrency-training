#pragma once

#include <iostream>
#include "common.h"

using namespace std;

void foo()
{
}

void otherOperations()
{
    // Throw a runtime exception stopping the program before
    // the thread gets to join in run()
    cout << "This is another operation" << endl;
    throw runtime_error("This is a runtime error");
}

void run_badPractice()
{
    // This example is meant to showcase a basic structure of real-world
    // applications with thread creations -> other operations -> join thread
    /*
    thread fooThread(foo);
    otherOperations();
    fooThread.join();
    */
    thread fooThread(foo);

    // One fix is to use try-catch block
    try
    {
        // Join does not execute in this example either since exception in
        // otherOperations() causes the code to jump down to the catch statement
        otherOperations();
        fooThread.join();
    }
    catch (const exception &e)
    {
        // join() must also be in catch statement in order to actually call join
        // ! This is still inefficient as real-world applications can have 100s of
        // ! threads and calling try-catch for each thread leads to inefficient code
        fooThread.join();
        cerr << e.what() << '\n';
    }

    // ? Thus we follow RAII -> Resource Acquisition in Initialization
    // ? Create a thread guard object that handles the construction and destruction of thread resources
}

// * This is correct implementation
// ? Once objects go out of scope due to exception raised,
// ? objects are destructed in reverse order
// * Therefore, ThreadGuard will call the join() of fooThread
// * when ThreadGuard destructor is called
void run()
{
    thread fooThread(foo);
    ThreadGuard tg(fooThread);
    try
    {
        otherOperations();
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    // Another Note: This main thread does not have to wait for join to
    // complete execution. The join call will automatically be called once
    // once function is complete and all destructors are called
    // ? Only need to call join in certain cases such as data handling
}