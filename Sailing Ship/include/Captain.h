#pragma once

#include <thread>
#include "common.h"

class Captain
{
private:
    void orderCleaners();
    void fullSpeedAhead();
    void stop();

    bool first = true;
    std::chrono::time_point<std::chrono::high_resolution_clock> cleanStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> cleanCurrent;

public:
    Captain();

    void commandHandler(int &command);

    ~Captain();
};