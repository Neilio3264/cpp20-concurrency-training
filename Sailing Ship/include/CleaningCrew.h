#pragma once

#include <chrono>
#include <iostream>

class CleaningCrew
{
private:
public:
    CleaningCrew();
    ~CleaningCrew();

    void operator()()
    {
        std::cout << "CLEANING: The Cleaning Crew is Preparing..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "CLEANING: Cleaning Crew Readying the Deck" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(7500));
        std::cout << "CLEANING: The Ship is now spotless" << std::endl;
    }
};

CleaningCrew::CleaningCrew() {}
CleaningCrew::~CleaningCrew() {}