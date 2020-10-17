#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <variant>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <ncurses.h>
#include <exception>
#include <chrono>
#include <thread>
#include <filesystem>

#include "include/sqlite_orm.h"
#include "include/MD5.h"
#include "src/SEPARATOR.h"
#include "src/split.h"
#include "src/spaceFilter.h"

#include "src/Task.h"
#include "src/Note.h"
#include "src/Deal.h"
#include "src/Important.h"
#include "src/Day.h"

#include "src/User.h"

#include "src/Session.h"
#include "src/AccountsDbManager.h"
#include "src/AccessProvider.h"
#include "src/NetWorker.h"

#include "src/CommandChecker.h"

int main()
{

    auto accountsDbManager = std::make_shared<AccountsDbManager>();
    auto user = std::make_shared<User>();
    //User user;
    auto accessProvider = std::make_shared<AccessProvider>(user, accountsDbManager);

    std::cout << "Welcome to CLICalendar. Please, log in or add new user" << std::endl;
    std::cout << "Write 'help' to get list of commands" << std::endl;
    std::cout << std::endl;

    while(1) {

        while (user->isLoggedIn() == false) {
            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');
            std::cout << std::endl;
            spaceFilter(input);

            std::vector<std::string> v = split(input, ' ');
            std::cin.clear();
            if ( v.size() == 1 ) {
                accessProvider->accessChecker(v[0], std::string(""));
            }
            else if ( v.size() == 2) {
                accessProvider->accessChecker(v[0], v[1]);
            }
            input.clear();
        }

        auto thisSession = std::make_shared<Session>(user);
        thisSession->localDb->sync_schema();

        boost::asio::io_service io_service;
        auto netWorker = std::make_shared<NetWorker>(thisSession);

        CommandChecker commandChecker(thisSession, accessProvider,  netWorker);

        while(user->isLoggedIn() == true) {

            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');
            spaceFilter(input);

            std::vector<std::string> v = split(input, ' ');
            std::cin.clear();

            if ( v.size() == 1 ) {
                commandChecker.commandMonitor(v[0], std::string(""), -1);
            }
            else if ( v.size() == 2) {
                commandChecker.commandMonitor(v[0], v[1], -1);
            }
            else if ( v.size() == 3) {
                    int arg3 = -1;
                try {
                    arg3 = std::stoi(v[2]);
                } catch(...) {
                    std::cout << "Third argument must be an integer!" << std::endl;
                    std::cout << "Try again" << std::endl;
                    std::cout << std::endl;
                    continue;
                }
                commandChecker.commandMonitor(v[0], v[1], arg3);
            }
            input.clear();
        }

    }
    return 0;
}
