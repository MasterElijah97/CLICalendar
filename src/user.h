#ifndef USER_H
#define USER_H


#include <memory>
#include <string>

#include "include/MD5.h"
#include "include/sqlite_orm.h"

#include "src/black_magic.h"

#include "src/iversion.h"
#include "src/iuniqueid.h"
#include "src/idatabase.h"

#include "src/session.h"

#include "src/deal.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"
//todo ptr on local db
class User {
    friend class Session;
    public:
        User() = default;
        User(const User& user) = delete;
        User(User&& user) = delete;
        User& operator=(const User& user) = delete;
        User& operator=(User&& user) = delete;

        User(std::string, std::string);

        ~User() = default;

        bool isLogged() const;
        std::string login_;
        std::string hashedPass_;
        int id_;
    private:
        bool isLoggedIn_;
        int key_;

        void key_gen();
        std::string doCryptoMessage(std::string);

        
};

#endif // USER_H
