#include <iostream>
#include <string>

#include "src/MD5.h"

using namespace sqlite_orm;

int main(int argc, char* argv[]) {

    auto accountsDb = make_storage("accounts.sqlite",
                                make_tablle("Accounts",
                                    make_column("id",
                                        &User::id_,
                                        autoincrement();
                                        primary_key()),
                                    make_column("login",
                                        &User::login_),
                                    make_column("hashed_pass",
                                        &User::hashedPass_ )));
    accountsDb.sync_schema();

    Session& thisSession = Session::instance();
    
    std::string databaseName;
    std::string arg1;
    std::string arg2;
    int arg3;

    // connect several clients

    //todo
    /*ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
    talk_to_svr::start(ep, login, password);
    service.run();*/

    std::cout << "Please, log in or add new account." << std::endl;
    std::cout << "Write 'help' command to see supported commands." << std::endl;

    while (!thisSession.user.isLoggedIn_) {
        std::cin >> arg1 >> arg2 >> arg3;
        commandMonitor(arg1, arg2, arg3, thisSession);
    }

    databaseName = thisSession.user.login_ + ".sqlite";

    auto localDb = make_storage(databaseName,
                                make_tablle("Days",

                                    make_column("id",
                                        &Day::id_,
                                        autoincrement();
                                        primary_key()),

                                    make_column("Date",
                                        &Day::date_),

                                    make_column("HashedPass",
                                        &User::hashedPass_ )),

                                make_tablle("Importants",

                                    make_column("id",
                                        &Important::id_,
                                        autoincrement();
                                        primary_key()),

                                    make_column("HashedPass",
                                        &Important::important_ )),

                                make_tablle("Deals",

                                    make_column("id",
                                        &Deal::id_,
                                        autoincrement();
                                        primary_key()),

                                    make_column("Name",
                                        &Deal::name_),

                                    make_column("Description",
                                        &Deal::description_),

                                    make_column("Label",
                                        &Deal::label_),

                                    make_column("Priority",
                                        &Deal::priority_),

                                    make_column("date",
                                        &Deal::date_),

                                    make_column("TimeBegin",
                                        &Time::begin),

                                    make_column("TimeBegin",
                                        &Time::end)),

                                make_tablle("Tasks",

                                    make_column("id",
                                        &Task::id_,
                                        autoincrement();
                                        primary_key()),

                                    make_column("IsCompleted",
                                        &Task::IsCompleted_),

                                    make_column("Description",
                                        &Task::description_)),

                                make_tablle("Notes",

                                    make_column("id",
                                        &Note::id_,
                                        autoincrement();
                                        primary_key()),

                                    make_column("Label",
                                        &Note::label_),

                                    make_column("Name",
                                        &Note::name_),

                                    make_column("Description",
                                        &Note::description_)),
        );

    localDb.sync_schema();

    thisSession->addBasePtr(&localDb);

    while (1) {
        std::cin >> arg1 >> arg2 >> arg3;
        commandMonitor(arg1, arg2, arg3, thisSession);
    }
}
