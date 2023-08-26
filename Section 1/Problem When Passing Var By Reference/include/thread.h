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