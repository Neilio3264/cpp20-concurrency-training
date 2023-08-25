#include "Captain.h"
#include "CleaningCrew.h"
#include "EngineCrew.h"

using namespace std;

Captain::Captain()
{
}

Captain::~Captain()
{
}

void Captain::commandHandler(int &command)
{
    if (command == 1)
    {
        cleanCurrent = chrono::high_resolution_clock::now();
        const chrono::duration<double, std::milli> elapsed = cleanCurrent - cleanStart;

        if (elapsed > chrono::milliseconds(7800) || first)
        {
            first = false;
            cleanStart = chrono::high_resolution_clock::now();
            CleaningCrew clean;
            thread cleanThread(clean);

            cleanThread.detach();
        }
        else
        {
            cout << "CLEANING: The Cleaning Crew is Busy..." << endl
                 << endl;
        }
    }
    else if (command == 2)
    {
        EngineCrew engine;
        thread engineThread(engine, ref(command));
        ThreadGuard tg(engineThread);
    }
    else if (command == 3)
    {
        EngineCrew engine;
        thread engineThread(engine, ref(command));
        ThreadGuard tg(engineThread);
    }
    else
    {
        cout << "Invalid Order, Please Give Another Order" << endl
             << endl;
    }
}