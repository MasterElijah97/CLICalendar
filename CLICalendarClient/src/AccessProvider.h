#ifndef ACCESSPROVIDER_H
#define ACCESSPROVIDER_H

#include <string>
#include <memory>

#include "../include/MD5.h"
#include "Session.h"
#include "AccountsDbManager.h"
#define NCURSES_NOMACROS
#include <ncurses.h>
//Helper
//Asks login and password, checks them, change password
struct AccessProvider {
    AccessProvider(std::shared_ptr<User>, std::shared_ptr<AccountsDbManager>);
    std::shared_ptr<User> user;
    std::shared_ptr<AccountsDbManager> accountsDbManager;
    void addingNewUser();
    void logIn();
    void logOut();
    void changePassword();
    void accessChecker(const std::string&, const std::string&);
private:
    void noechoInput(std::string&, char*);
};


#endif // ACCESSPROVIDER_H