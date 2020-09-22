#ifndef USER_H
#define USER_H


#include <memory>
#include <string>

#include "src/deal.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"
#include "src/sqlite_orm.h"
//todo ptr on local db
class User {
    public:
        User() = delete;
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
            this->encryptingKey = key;
        }

        void setDecryptKey(std::string key) {
            this->decryptingKey = key;
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
    private:
        std::string login_;
        std::string hashedPass_;
        std::string encryptingKey_;
        std::string decryptingKey_;
        int id;

        std::shared_ptr<sqlite3db> localDb = std::make_shared<sqlite3db>(new sqlite3db);
};

#endif // USER_H
