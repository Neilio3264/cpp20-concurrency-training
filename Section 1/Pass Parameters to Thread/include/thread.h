#pragma once

#include <iostream>
#include "common.h"

using namespace std;

void functionOne(int x, int y)
{
    cout << "X + Y = " << (x + y) << endl;
}

void functionTwo(int &x)
{
    while (true)
    {
        cout << "Thread 2 value of X - " << x << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void run()
{
    int p = 9;
    int q = 8;
    thread threadOne(functionOne, p, q);
    threadOne.join();

    thread threadTwo(functionTwo, ref(p));
    ThreadGuard tg(threadTwo);
    this_thread::sleep_for(chrono::milliseconds(5000));

    p = 15;
    cout << "Main thread value of X has been changed to - " << p << endl;
    threadTwo.join();
}