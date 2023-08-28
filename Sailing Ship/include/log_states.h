#ifndef ZOTIKOS_LOG_STATES_H
#define ZOTIKOS_LOG_STATES_H

namespace zotikos
{
    enum class log_state
    {
        BEGIN,
        ENGINE_COMMAND_ISSUED,
        ENGINE_CREW_WORKING,
        CLEAN_COMMAND_ISSUED,
        CLEAN_CREW_WORKING,
        QUIT,
        ERROR
    };
}

#endif