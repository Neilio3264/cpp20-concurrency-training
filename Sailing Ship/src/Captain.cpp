#include "Captain.h"
#include "zotikos.h"

using namespace std;

Captain::Captain()
{
    logFileName = "";
}

Captain::Captain(std::string &logFileName)
{
    this->logFileName = logFileName;

    thread engineCrew(this->engine, ref(this->logFileName), ref(this->engine.returnQueueRef()));
    engineCrew.detach();

    auto temp = this->clean.returnQueueRef();
    thread cleanCrew(this->clean, ref(this->logFileName), ref(this->clean.returnQueueRef()));
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

void Captain::commandHandler(int &code)
{
    LogData ld;

    switch (code)
    {
    case 1:
        ld.state = zotikos::log_state::CLEAN_COMMAND_ISSUED;
        issueCleanCommand();
        ld.argument = "Captain has issued a new clean command";
        break;

    case 2:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        issueEngineCommand(code);
        ld.argument = "Captain has issued a new full speed ahead engine command";
        break;

    case 3:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        issueEngineCommand(code);
        ld.argument = "Captain has issued a new stop engine command";
        break;

    case 100:
        ld.state = zotikos::log_state::QUIT;
        ld.argument = "Stop command issued to all systems";
        break;

    default:
        ld.state = zotikos::log_state::ERROR;
        ld.argument = "Input Entered in not Command Code. Please Try Again.";
        break;
    }

    logger::log(logFileName, ld.state) << ld.argument;
}

Captain::~Captain()
{
    clean.setQuit();
    engine.setQuit();
}