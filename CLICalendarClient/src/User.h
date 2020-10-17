#ifndef USER_H
#define USER_H

#include <string>
#include "../include/MD5.h"

class User {

    friend class Session;

    public:
        //id as primary key in database
        int id_;

        User();
        User(std::string, std::string);

        //destructor
        ~User() = default;

        //getter
        bool isLoggedIn() const;

        //members
        std::string login_;
        std::string hashedPass_;
        bool isLoggedIn_;        //flag

    private:
        //need for ciphering data
        //will be in use in future
        int key_;
        void key_gen();
        std::string doCryptoMessage(std::string); //just XOR
};

#endif // USER_H
