#include "log_stream.h"
#include "logger.h"

namespace zotikos
{
    logStream::logStream(logger &log, log_state state) : _logger(log), _state(state)
    {
    }

    logStream::~logStream()
    {
        _logger.push(get_time() + get_state() + str());
    }

    const std::string logStream::get_state()
    {
        std::string action;
        switch (_state)
        {
        case log_state::BEGIN:
            action = "[START] ";
            break;

        case log_state::ENGINE_COMMAND_ISSUED:
            action = "[CAPTAIN ISSUES ENGINE COMMAND] ";
            break;

        case log_state::ENGINE_CREW_WORKING:
            action = "[ENGINE CREW] ";
            break;

        case log_state::CLEAN_COMMAND_ISSUED:
            action = "[CAPTAIN ISSUES CLEANING COMMAND] ";
            break;

        case log_state::CLEAN_CREW_WORKING:
            action = "[CLEANING CREW] ";
            break;

        case log_state::QUIT:
            action = "[STOP] ";
            break;

        case log_state::ERROR:
            action = "[ERROR] ";
            break;
        }

        return action;
    }

    const std::string logStream::get_time()
    {
        return zotikos::getDateTimeStr();
    }
}