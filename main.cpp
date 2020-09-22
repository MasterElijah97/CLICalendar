#include <iostream>
#include <string>

#include "src/MD5.h"

using namespace sqlite_orm;
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


int main(int argc, char* argv[]) {

    Session& thisSession = Session::instance();

    // connect several clients

    //todo
    /*ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
    talk_to_svr::start(ep, login, password);
    service.run();*/

    std::cout << "Please, log in or add new account." << std::endl;
    std::cout << "Write 'help' command to see supported commands." << std::endl;

    std::string arg1;
    std::string arg2;
    int arg3;

    while (1) {
        std::cin >> arg1 >> arg2 >> arg3;
        commandMonitor(arg1, arg2, arg3, thisSession);
    }
}
