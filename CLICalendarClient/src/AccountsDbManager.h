#ifndef ACCOUNTSDBMANAGER_H
#define ACCOUNTSDBMANAGER_H

#include <memory>
#include "Session.h"

//Class-helper
//Wraps database with accounts
class AccountsDbManager {
    public:
        AccountsDbManager();
        std::shared_ptr<Accounts> accountsDb = nullptr;
};

#endif // ACCOUNTSDBMANAGER_H
