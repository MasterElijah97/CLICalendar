#include <iostream>
#include <string>

#include "src/MD5.h"

std::string arg1;
std::string arg2;
int arg3;

int main(int argc, char* argv[]) {

    Session& thisSession = Session::instance();

    unsigned char key[16] = md5(password);
    thisSession->setPassword(md5(password));

    // connect several clients
    ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
    talk_to_svr::start(ep, login, password);
    service.run();

    while (1) {
        std::cin >> arg1 >> arg2 >> arg3;
        commandMonitor(arg1, arg2, arg3);
    }
}
