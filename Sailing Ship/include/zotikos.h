#include "logger.h"

using namespace zotikos;

struct LogData
{
    std::string argument;
    zotikos::log_state state;
};

LogData inputHandler(int &command, std::string &message, Captain &captain)
{
    LogData ld;
    ld.argument = message;

    switch (command)
    {
    case 1:
        ld.state = zotikos::log_state::CLEAN_COMMAND_ISSUED;
        break;

    case 2:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        break;

    case 3:
        ld.state = zotikos::log_state::ENGINE_COMMAND_ISSUED;
        break;

    case 100:
        ld.state = zotikos::log_state::QUIT;
        break;

    default:
        ld.state = zotikos::log_state::ERROR;
        ld.argument = "Input Entered in not Command Code";
        break;
    }

    return ld;
}