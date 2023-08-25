#pragma once

#include <iostream>
#include <thread>

using namespace std;

void test()
{
    cout << "Hello from test " << this_thread::get_id() << endl;
}

void functionA()
{
    cout << "Hello from function A " << this_thread::get_id() << endl;

    thread threadC(test);
    threadC.join();
}

void functionB()
{
    cout << "Hello from function B " << this_thread::get_id() << endl;
}

void run()
{
    cout << "Hello from main " << this_thread::get_id() << endl;

    thread threadA(functionA);
    thread threadB(functionB);

    threadA.join();
    threadB.join();

    cout << "Hello from main again " << this_thread::get_id() << endl;
}