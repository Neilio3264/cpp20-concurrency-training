#pragma once

#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include "zotikos.h"

class CleaningCrew
{
private:
    std::queue<std::string> workQueue;
    bool quit = false;

public:
    void setQuit()
    {
        this->quit = true;
    }

    void addCommand()
    {
        this->workQueue.push("clean");
    }

    void operator()(std::string &logger)
    {
        while (!quit)
        {
            if (!workQueue.empty())
            {
                logger::log(logger, zotikos::log_state::CLEAN_CREW_WORKING) << "New Command Received";
                logger::log(logger, zotikos::log_state::CLEAN_CREW_WORKING) << "Cleaning Crew is Preparing...";
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                logger::log(logger, zotikos::log_state::CLEAN_CREW_WORKING) << "Cleaning Crew Readying the Deck";
                std::this_thread::sleep_for(std::chrono::milliseconds(7500));
                logger::log(logger, zotikos::log_state::CLEAN_CREW_WORKING) << "The Ship is now spotless";

                workQueue.pop();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }
};