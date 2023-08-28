#include "Captain.h"
#include "zotikos.h"

using namespace std;

Captain::Captain()
{
}

Captain::Captain(std::string &logFileName)
{
    thread engineCrew(this->engine, logFileName);
    engineCrew.detach();

    thread cleanCrew(this->clean, logFileName);
    cleanCrew.detach();
}

void Captain::issueCleanCommand()
{
    clean.addCommand();
}

void Captain::issueEngineCommand(int &code)
{
    engine.addCommand(code);
}

Captain::~Captain()
{
    clean.setQuit();
    engine.setQuit();
}