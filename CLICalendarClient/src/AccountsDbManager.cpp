#include "AccountsDbManager.h"

AccountsDbManager::AccountsDbManager() {
    this->accountsDb = std::make_shared<Accounts>(initAccountsDb());
    this->accountsDb->sync_schema();
}
