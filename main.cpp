#include <iostream>
#include <string>

#include "include/MD5.h"
#include "include/sqlite_orm.h"
using namespace sqlite_orm;
#include "src/black_magic.h"
#include "src/session.h"
#include "src/deal.h"
#include "src/important.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"
#include "src/user.h"

/* WARNING!!!
 * For educational purposes only!!!
 * Never do this way  in serious projects
 */


int main(int argc, char* argv[]) {

    auto accountsDb = make_storage("accounts.sqlite",
                                make_tablle("Accounts",
                                    make_column("id",
                                        &User::id_,
                                        autoincrement(),
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

    base_t localDb = make_storage(databaseName,
                                make_table("Days",

                                    make_column("id",
                                        &Day::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Day::version_),

                                    make_column("Date",
                                        &Day::date_)),

                                make_table("Importants",

                                    make_column("id",
                                        &Important::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Important::version_),

                                    make_column("HashedPass",
                                        &Important::important_ )),

                                make_table("Deals",

                                    make_column("id",
                                        &Deal::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Deal::version_),

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
                                        &Deal::Time::begin),

                                    make_column("TimeEnd",
                                        &Deal::Time::end)),

                                make_table("Tasks",

                                    make_column("id",
                                        &Task::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Task::version_),

                                    make_column("IsCompleted",
                                        &Task::isCompleted_),

                                    make_column("Description",
                                        &Task::description_)),

                                make_table("Notes",

                                    make_column("id",
                                        &Note::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Note::version_),

                                    make_column("Label",
                                        &Note::label_),

                                    make_column("Name",
                                        &Note::name_),

                                    make_column("Description",
                                        &Note::description_))
    );

    localDb.sync_schema();

    thisSession.addBasePtr(&localDb);

    while (1) {
        std::cin >> arg1 >> arg2 >> arg3;
        commandMonitor(arg1, arg2, arg3, thisSession);
    }
}
