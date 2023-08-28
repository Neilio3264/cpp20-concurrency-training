#include "logger.h"

using namespace zotikos;

struct LogData
{
    std::string argument;
    zotikos::log_state state;
};

LogData inputHandler(int &command, Captain &captain)
{
    LogData ld;
    ld.argument = "";

    switch (command)
    {
    case 1:
        ld.state = zotikos::log_state::CLEAN_COMMAND_ISSUED;
        captain.issueCleanCommand();
        ld.argument = "Captain has issued a new clean command";
        break;

    case 2:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        captain.issueEngineCommand(command);
        ld.argument = "Captain has issued a new full speed ahead engine command";
        break;

    case 3:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        captain.issueEngineCommand(command);
        ld.argument = "Captain has issued a new stop engine command";
        break;

    case 100:
        ld.state = zotikos::log_state::QUIT;
        ld.argument = "Stop command issued to all systems";
        captain.~Captain();
        break;

    default:
        ld.state = zotikos::log_state::ERROR;
        ld.argument = "Input Entered in not Command Code. Please Try Again.";
        break;
    }

    return ld;
}