#include "User.h"

User::User() {
    this->isLoggedIn_ = false;
    this->id_         = -1;
}

User::User(std::string login, std::string hashedPass) {
    this->login_      = login;
    this->hashedPass_ = hashedPass;
    this->id_         = -1;
}

bool User::isLoggedIn() const {
	return this->isLoggedIn_;
}

std::string User::doCryptoMessage(std::string message) {
    for (auto &i : message) {
        i ^= key_;
    }

    return message;
}

void User::key_gen() {
    int i = 0;
    std::string keyString = md5(this->hashedPass_);
    for (auto &ch : keyString) {
        i += ch;
    }

    if (i % 2 == 0) {
        this->key_ = i + 1;
    } else {
        this->key_ = i;
    }
}
