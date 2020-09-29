#include "src/commandMonitor.h"

void clearConsole() {
    for (int i = 0; i != 100; ++i) {
        std::cout << "\n";
    }
}

//need to add if isLoggedIn_ = true
void commandMonitor(const std::string& arg1,
                    const std::string& arg2,
                    const int& arg3,
                    Session& thisSession) {

    //method compare returns 0 if string are fully equal
    if (!arg1.compare("next")) {
        std::visit(JoinedIncrementAllower{thisSession}, thisSession.joinedObject_);  

        thisSession->showJoined();
    }
    else if (!arg1.compare("prev")) {
        std::visit(JoinedDecrementAllower{thisSession}, thisSession.joinedObject_);  

        thisSession->showJoined();
    }
    else if (!arg1.compare("join")) {

        if (!arg2.compare("deals")) {
            if(!joinedObject_) {
                std::cout << "Please, open days" << std::endl;
            } else {
                thisSession.setJoined(joinedObject_->deals.end() - 1);
            }
        }

    } 
    else if (!arg1.compare("create")) {

        if (!arg2.compare("task")) {

            thisSession.creatingTask();

        } else if (!arg2.compare("note")) {

            thisSession.creatingNote();

        } else if (!arg2.compare("day")) {

            thisSession.creatingDay();

        } else if (!arg2.compare("deal")){

            thisSession.creatingDeal();

        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    } 
    else if (!arg1.compare("edit")) {

        thisSession.joinedObject_->edit();

    } 
    else if (!arg1.compare("copy")) {

        thisSession.setCopyable(joinedObject_);

    } 
    else if (!arg1.compare("paste")) {

        std::visit(CopyablePaster{thisSession}, copyableObject_);

    } 
    else if (!arg1.compare("remove")) {

        if (!arg2.compare("task")) {

            thisSession.localDb->remove<Task>(thisSession.joinedObject_->id_);
            tasks_.erase(joinedObject_);

        } else if (!arg2.compare("note")) {

            thisSession.localDb->remove<Note>(thisSession.joinedObject_->id_);
            notes_.erase(joinedObject_);

        } else if (!arg2.compare("day")) {

            thisSession.localDb->remove<Day>(thisSession.joinedObject_->id_);
            days_.erase(joinedObject_);

        } else if (!arg2.compare("deal")) {

            thisSession.localDb->remove<Deal>(thisSession.joinedObject_->deals_[arg3-1].id_);
            joinedObject_->removeDeal(arg3);

        } else if (!arg2.compare("important")) {

            thisSession.localDb->remove<Important>(thisSession.joinedObject_->importants_[arg3-1].id_);
            joinedObject_->removeImportant(arg3);

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;

        }
    } 
    else if (!arg1.compare("open")) {

        if (!arg2.compare("tasks")) {

            thisSession.setJoined(tasks_.end() - 1);
            thisSession.showJoined();

        } else if (!arg2.compare("notes")) {

            thisSession.setJoined(notes_.end() - 1);
            thisSession.showJoined();

        } else if (!arg2.compare("days")) {

            thisSession.setJoined(days_.end() - 1);
            thisSession.showJoined();

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;

        }
    } 
    else if (!arg1.compare("login")) {

        thisSession.logIn();

    } 
    else if (!arg1.compare("logout")) {

        thisSession.logOut();

    } 
    else if (!arg1.compare("connect")) {

        t//hisSession.connectToServer(); //todo

    } 
    else if ((!arg1.compare("disconnect"))) {

        //thisSession.disconnectFromServer(); //todo

    }
    else if (arg1 == "sync") {

        //thisSession.syncBases(); //todo

    }
    else if (arg1 == "add") {

        if (arg2 == "user") {
            thisSession.addingNewUser();
        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    } 
    else if (arg1 == "exit") {

        //thisSession.syncBases(); // todo
        //thisSession.disconnectFromServer(); //todo
        thisSession.logOut();

    } 
    else if (arg1 == "help") {

        thisSession.showHelp();

    }
    else {
        std::cout << "Wrong command. Please, check 'help'" << std::endl;
    }

}
