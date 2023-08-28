#pragma once

#include <chrono>
#include <iostream>

class EngineCrew
{
private:
    std::queue<int> workQueue;
    bool quit = false;

public:
    void setQuit()
    {
        this->quit = true;
    }

    void addCommand(int &code)
    {
        this->workQueue.push(code);
    }

    void operator()(std::string &logger)
    {
        while (!quit)
        {
            if (!workQueue.empty())
            {
                logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "New Command Received";
                logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "Engine Crew is Preparing...";
                std::this_thread::sleep_for(std::chrono::milliseconds(300));

                if (workQueue.front() == 2)
                {
                    logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "Preparing the Engines!";
                    std::this_thread::sleep_for(std::chrono::milliseconds(3500));
                    logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "Now going Full Speed Ahead!";
                }
                else
                {
                    logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "Stopping all Engines!";
                    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                    logger::log(logger, zotikos::log_state::ENGINE_CREW_WORKING) << "All Engines Stopped!";
                }

                workQueue.pop();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }
};