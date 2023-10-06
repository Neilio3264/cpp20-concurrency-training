#pragma once

#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <numeric>

using namespace std;

int add(int x, int y)
{
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Add function runs in : " << this_thread::get_id() << endl;
    return x + y;
}

// * Pass wrapper to thread to run asynchronously
void taskThread()
{
    packaged_task<int(int, int)> task(add);
    future<int> future = task.get_future();

    // ? Packaged task is not copyable, must use std::move
    thread t(move(task), 5, 6);
    t.detach();

    cout << "Task Thread - " << future.get() << "\n";
}

// * This wrapper will run synchronously
void taskNormal()
{
    packaged_task<int(int, int)> task(add);
    future<int> future = task.get_future();
    // ? Unlike async, the function does not auto run after creation
    task(7, 8);
    cout << "Task Normal - " << future.get() << endl;
}

void run()
{
    taskThread();
    taskNormal();
    cout << "Main Thread ID: " << this_thread::get_id() << endl;
}