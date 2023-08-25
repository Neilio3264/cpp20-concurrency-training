#pragma once

#include <chrono>
#include <iostream>

class EngineCrew
{
private:
public:
    EngineCrew();
    ~EngineCrew();

    void operator()(int &command)
    {
        std::cout << "ENGINE: The Engine Crew is Preparing..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "ENGINE: Engine Crew Ready!";
        if (command == 2)
        {
            std::cout << " Preparing the Engines!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3500));
            std::cout << "ENGINE: Now going Full Speed Ahead!" << std::endl;
        }
        else if (command == 3)
        {
            std::cout << " Stopping all engines!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            std::cout << "ENGINE: All engines stopped!" << std::endl;
        }
    }
};

EngineCrew::EngineCrew() {}
EngineCrew::~EngineCrew() {}