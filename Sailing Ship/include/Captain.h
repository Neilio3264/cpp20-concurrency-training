#pragma once

#include <thread>
#include "CleaningCrew.h"
#include "EngineCrew.h"

class Captain
{
private:
    EngineCrew engine;
    CleaningCrew clean;

public:
    Captain();
    Captain(std::string &logFileName);

    void issueCleanCommand();
    void issueEngineCommand(int &code);

    ~Captain();
};