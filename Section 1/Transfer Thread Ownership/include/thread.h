#pragma once

#include <iostream>
#include "common.h"

using namespace std;

void foo()
{
}

void bar()
{
}

void run()
{
    thread threadOne(foo);

    // ! Thread objects are not copy assignable
    // thread threadTwo = threadOne;

    // * Explicitly transfer ownership
    // ? Owner of the Thread object must manage thread lifecycle
    // ? In this case, the Main Thread
    thread threadTwo = move(threadOne);

    // ? This implicitly calls std::move() since it is a temp object
    threadOne = thread(bar);

    thread threadThree(foo);
    // ! This will throw an exception
    // * Must manage thread lifecycle explicitly
    // * Cannot just dump one thread and assign a new thread
    threadOne = move(threadThree);

    threadOne.join();
    threadTwo.join();
    threadThree.join();
}