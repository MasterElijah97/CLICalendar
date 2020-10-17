#ifndef ACCOUNTSDBMANAGER_H
#define ACCOUNTSDBMANAGER_H

#include <memory>
#include "Session.h"

class AccountsDbManager {
    public:
        AccountsDbManager();
        std::shared_ptr<Accounts> accountsDb = nullptr;
};

#endif // ACCOUNTSDBMANAGER_H
