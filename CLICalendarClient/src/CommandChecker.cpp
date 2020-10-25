#include "CommandChecker.h"

CommandChecker::CommandChecker(std::shared_ptr<Session> session,
                               std::shared_ptr<AccessProvider> accessProvider,
                               std::shared_ptr<NetWorker> netWorker) {

    this->thisSession = std::move(session);
    thisSession->localDb->sync_schema();
    this->accessProvider = std::move(accessProvider);
    this->netWorker = std::move(netWorker);
}

void CommandChecker::clearConsole() {
    for (int i = 0; i != 100; ++i) {
        std::cout << "\n";
    }
}
void CommandChecker::commandMonitor(const std::string& arg1,
                                    const std::string& arg2,
                                    const std::size_t& arg3) {

    if (!arg1.compare("next")) {

        thisSession->incrementJoined();

    }
    else if (!arg1.compare("prev")) {

        thisSession->decrementJoined();

    }
    else if (!arg1.compare("edit") && !arg2.compare("deal")) {

        thisSession->editDeal(arg3);

    }
    else if (!arg1.compare("edit") && !arg2.compare("important")) {

        thisSession->editImportant(arg3);

    }
    else if (!arg1.compare("create")) {

        if (!arg2.compare("task")) {

            thisSession->creatingTask();

        } else if (!arg2.compare("note")) {

            thisSession->creatingNote();

        } else if (!arg2.compare("day")) {

            thisSession->creatingDay();

        } else if (!arg2.compare("deal")){

            thisSession->creatingDeal();

        }  else if (!arg2.compare("important")){

            thisSession->creatingImportant();

        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    }
    else if (!arg1.compare("edit")) {

        thisSession->editItem();

    }
    else if (!arg1.compare("copy")) {

        thisSession->copyItem();
    }
    else if (!arg1.compare("paste")) {

        thisSession->pasteItem();

    }
    else if (!arg1.compare("move")) {

        thisSession->moveItem();

    }
    else if (!arg1.compare("here")) {

        thisSession->pasteMoveableItem();

    }
    else if (!arg1.compare("remove")) {

        if (!arg2.compare("task")) {

            thisSession->removeTask();

        } else if (!arg2.compare("note")) {

            thisSession->removeNote();

        } else if (!arg2.compare("day")) {

            thisSession->removeDay();

        } else if (!arg2.compare("deal")) {

           thisSession->removeDeal(arg3);

        } else if (!arg2.compare("important")) {

            thisSession->removeImportant(arg3);

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }
    else if (!arg1.compare("open")) {

        if (!arg2.compare("tasks")) {

            thisSession->openTasks();

        } else if (!arg2.compare("notes")) {

            thisSession->openNotes();

        } else if (!arg2.compare("days")) {

            thisSession->openDays();

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }

    else if (!arg1.compare("log")) {

        if (!arg2.compare("out")) {

            this->accessProvider->logOut();

        }

    }
    else if (!arg1.compare("connect")) {

        this->netWorker->connect();

    }
    else if ((!arg1.compare("disconnect"))) {

        this->netWorker->disconnect();

    }
    else if (!arg1.compare("sync")) {

        this->netWorker->sync();

    }
    else if (!arg1.compare("exit")) {

        accessProvider->logOut();
        exit(0);

    }
    else if (!arg1.compare("help")) {

        thisSession->showHelp();

    }
    else if (!arg1.compare("change")) {

        if (!arg2.compare("password")) {

            this->accessProvider->changePassword();

        } else {

            std::cout << "Wrong second argument: " << arg2 << std::endl;
            std::cout << "Did you mean 'password'? " << std::endl;

        }

    }
    else {
        std::cout << "Wrong command. Please, check 'help'" << std::endl;
        std::cout << std::endl;
    }
}
