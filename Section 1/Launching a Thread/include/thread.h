#pragma once

#include <iostream>
#include <thread>

void foo()
{
    std::cout << "Hello from foo " << std::this_thread::get_id() << std::endl;
}

class Callable
{
public:
    void operator()()
    {
        std::cout << "Hello from class with function call operator " << std::this_thread::get_id() << std::endl;
    }
};

void run()
{
    std::thread thread1(foo);

    Callable obj;
    std::thread thread2(obj);

    std::thread thread3([]
                        { std::cout << "Hello from lambda " << std::this_thread::get_id() << std::endl; });

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Hello from main " << std::this_thread::get_id() << std::endl;
}