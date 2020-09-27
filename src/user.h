#ifndef USER_H
#define USER_H


#include <memory>
#include <string>

#include "src/session.h"

#include "src/deal.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"
#include "src/sqlite_orm.h"
//todo ptr on local db
class User {
    friend class Session;
    public:
        User() = default;
        User(const User& user) = delete;
        User(User&& user) = delete;
        User& operator=(const User& user) = delete;
        User& operator=(User&& user) = delete;

        User(std::string login, std::string hashedPass) {
            this->login = login;
            this->hashedPass = hashedPass;
        }

        ~User() {

        }

        //getters

        //setters
        void setEncryptingKey(std::string key) {
            this->encryptingKey = std::move(key);
        }

        void setDecryptKey(std::string key) {
            this->decryptingKey = std::move(key);
        }
        //other funcs
        std::string encryptMessage(std::string message) {
            //todo
            //encrypting function
        }

        std::string decryptMessage(std::string message) {
            //todo
            //decrypting function
        }

        std::string syncFromLocalToServerDb() {
            try {

            }
            catch(...) {
                std::cout << "Something get wrong. Try again later" << std::endl;
            }
            std::cout << "All data have been synchronized from local to server database" << std::endl;
        }

        std::string syncFromServerToLocalDb() {
            try {

            }
            catch(...) {
                std::cout << "Something get wrong. Try again later" << std::endl;
            }
            std::cout << "All data have been synchronized from server to local database" << std::endl;
        }
    
    bool isLogged() const {
        return isLoggedIn_;
    }
    
        std::string login_;
        std::string hashedPass_;
        int id_;
    private:
        bool isLoggedIn_;
        std::string encryptingKey_;
        std::string decryptingKey_;
};

#endif // USER_H
