#ifndef COMMANDCHECKER_H
#define COMMANDCHECKER_H

#define NCURSES_NOMACROS //need to avoid conflicts in function names
#include <ncurses.h>
#include <memory>
#include <string>

#include "Session.h"
#include "AccessProvider.h"
#include "NetWorker.h"

//Class-helper
//Handle user's input
struct CommandChecker {
    CommandChecker(std::shared_ptr<Session>,
                   std::shared_ptr<AccessProvider>,
                   std::shared_ptr<NetWorker>);

    std::shared_ptr<Session> thisSession;
    std::shared_ptr<AccessProvider> accessProvider;
    std::shared_ptr<NetWorker> netWorker;

    void clearConsole();
    void commandMonitor(const std::string&,
                        const std::string&,
                        const std::size_t&);
};

#endif // COMMANDCHECKER_H
