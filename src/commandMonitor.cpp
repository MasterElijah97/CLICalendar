#include "src/commandMonitor.h"

void clearConsole() {
    for (int i = 0; i != 100; ++i) {
        std::cout << "\n";
    }
}

void commandMonitor(const std::string& arg1,
                    const std::string& arg2,
                    const int& arg3) {



    if (!strncmp(arg1, "join") {

        if (!strncmp(arg2, "deals")) {

        } else {

        }

    } else if (arg1 == "create") {

        if (arg2 == "task") {
            thisSession->creatingTask();
        } else if (arg2 == "note") {
            thisSession->creatingNote();
        } else if (arg2 == "day") {
            thisSession->creatingDay();
        } else if (arg2 == "deal"){
            thisSession->creatingDeal();
        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    } else if (arg1 == "edit") {

        if (std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::vector<Task>::iterator>)
                return "task";
            else if constexpr (std::is_same_v<T, std::vector<Note>::iterator>)
                return "note";
            else if constexpr (std::is_same_v<T, std::vector<Day>::iterator>)
                return "day";
            else if constexpr (std::is_same_v<T, std::vector<Deal>::iterator>)
                return "deal";
        }, thisSession->getJoined();) == "task") {

            if (arg2 == "label") {
                thisSession->setJoinedLabel();
            } else if (arg2 == "description") {
                thisSession->setJoinedDescription();
            } else {

            }

        } else if (std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::vector<Task>::iterator>)
                return "task";
            else if constexpr (std::is_same_v<T, std::vector<Note>::iterator>)
                return "note";
            else if constexpr (std::is_same_v<T, std::vector<Day>::iterator>)
                return "day";
            else if constexpr (std::is_same_v<T, std::vector<Deal>::iterator>)
                return "deal";
        }, joined) == "note") {

            if (arg2 == "label") {
                thisSession->setJoinedLabel();
            } else if (arg2 == "name") {
                thisSession->setJoinedName();
            } else if (arg2 == "description") {
                thisSession->setJoinedDescription();
            } else {

            }

        } else if (std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::vector<Task>::iterator>)
                return "task";
            else if constexpr (std::is_same_v<T, std::vector<Note>::iterator>)
                return "note";
            else if constexpr (std::is_same_v<T, std::vector<Day>::iterator>)
                return "day";
            else if constexpr (std::is_same_v<T, std::vector<Deal>::iterator>)
                return "deal";
        }, joined) == "day") {

            if (arg2 == "label") {
                thisSession->setJoinedLabel();
            } else if (arg2 == "description") {
                thisSession->setJoinedDescription();
            } else {

            }

        } else if (std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::vector<Task>::iterator>)
                return "task";
            else if constexpr (std::is_same_v<T, std::vector<Note>::iterator>)
                return "note";
            else if constexpr (std::is_same_v<T, std::vector<Day>::iterator>)
                return "day";
            else if constexpr (std::is_same_v<T, std::vector<Deal>::iterator>)
                return "deal";
        }, joined) == "deal") {

            if (arg2 == "label") {
                thisSession->setJoinedLabel();
            } else if (arg2 == "name") {
                thisSession->setJoinedName();
            } else if (arg2 == "time") {
                thisSession->setJoinedTime();
            } else if (arg2 == "description") {
                thisSession->setJoinedDescription();
            } else if (arg2 == "priority") {
                thisSession->setJoinedPriority();
            } else {

            }

        }

    } else if (arg1 == "copy") {

        thisSession->setCopyable(joinedObject_);

    } else if (arg1 == "paste") {

        thisSession->setJoined(copyableObject_);

    } else if (arg1 == "remove") {

        if (arg2 == "task") {
            tasks_.erase(joinedObject_);
        } else if (arg2 == "note") {
            notes_.erase(joinedObject_);
        } else if (arg2 == "day") {
            days_.erase(joinedObject_);
        } else if (arg2 == "deal") {
            joined->removeDeal(arg3);
        } else if (arg2 == "important") {
            joined->removeImportant(arg3);
        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }
    } else if (arg1 == "open") {

        if (arg2 == "tasks") {
            tasks.end()->show();
        } else if (arg2 == "notes") {
            notes.end()->show();
        } else if (arg2 == "days"){
            days.end()->show();
        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }
    } else if (arg1 == "login") {
        logIn();
    } else if (arg1 == "logout") {
        disconnectFromServer();
        logOut();
    } else if (arg1 == "connect") {
        connectToServer();
    } else if (arg1 == "sync") {
        syncBases();
    } else if (arg1 == "add") {

        if (arg2 == "user") {
            addingNewUser();
        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    } else if (arg1 == "exit") {
        syncBases();
        disconnectFromServer();
        logOut();
    } else {
        std::cout << "Wrong command. Please, check 'help'" << std::endl;
    }

}
