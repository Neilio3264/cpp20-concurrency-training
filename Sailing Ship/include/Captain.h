#pragma once

#include <thread>
#include "CleaningCrew.h"
#include "EngineCrew.h"

class Captain
{
private:
    EngineCrew engine;
    CleaningCrew clean;

    std::string logFileName;

public:
    Captain();
    Captain(std::string &logFileName);

    void issueCleanCommand();
    void issueEngineCommand(int &code);

    void commandHandler(int &code);

    ~Captain();
};