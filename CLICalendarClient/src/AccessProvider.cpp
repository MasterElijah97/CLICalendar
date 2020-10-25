#include "AccessProvider.h"

void AccessProvider::noechoInput(std::string& password, const char* msg = "Password: ") {
    //initializing c-style string
    const int MAX_PASSWORD_SIZE = 50;
    char str[MAX_PASSWORD_SIZE];
    for (int i = 0; i != MAX_PASSWORD_SIZE; i++) {
        str[i] = '`';
    }
    //ncurses.h works here: getting inpit with noecho
    initscr();
    noecho();
    printw(msg);
    scanw("%s", str);

    //copy user's input in c++ string
    std::string pass(str, MAX_PASSWORD_SIZE);
    //clear garbage
    for (auto it = pass.begin(); it != pass.end(); ++it) {
        if ( (*it) == '`' ) {
            pass.erase(it, pass.end());
            break;
        }
    }

    password = std::move(pass);
    //clear ncurses screen and close ncurses
    clear();
    endwin();
}

AccessProvider::AccessProvider(std::shared_ptr<User> user, std::shared_ptr<AccountsDbManager> accountsDbManager) {
    this->user = std::move(user);
    this->accountsDbManager = std::move(accountsDbManager);
}

void AccessProvider::addingNewUser() {

    std::string login;
    std::string password;

    std::cout << "Please, enter new login" << std::endl;
    std::getline(std::cin, login, '\n');

        std::vector<User> isUserExists = this->accountsDbManager->accountsDb->get_all<User>(where(is_equal(&User::login_, login)));

        if (isUserExists.empty()) {

            std::cout << "Please, enter new password" << std::endl;
            noechoInput(password);

            this->user->login_ = std::move(login);
            this->user->hashedPass_ = md5(password);

            auto insertedId = this->accountsDbManager->accountsDb->insert(*(this->user));
            this->user->id_ = insertedId;

            std::cout << "New account has been created" << std::endl;
            std::cout << "Now you can log in with entered login and password" << std:: endl;
            std::cout << std::endl;

        } else {
            std::cout << "Sorry, this login is already exists. Please, try again." << std::endl;
            std::cout << std::endl;
        }
}

void AccessProvider::logIn() {

    std::string login;
    std::string password;
    std::string hashedPassword;

    std::cout << "Login: ";
    std::getline(std::cin, login, '\n');
    std::cout << std::endl;

    noechoInput(password);
    std::cout << "Password: " << std::endl;
    std::cout << std::endl;

    hashedPassword = md5(password);

    auto ExistingUser = this->accountsDbManager->accountsDb->get_all<User>(where(is_equal(&User::login_, login) &&
                                                                                 is_equal(&User::hashedPass_, hashedPassword)));
    if (!ExistingUser.empty()) {
        this->user->login_ = std::move(login);
        this->user->hashedPass_ = std::move(hashedPassword);
        std::cout << "You've succesfully logged in" << std::endl;
        std::cout << std::endl;
        this->user->isLoggedIn_ = true;
    } else {
        std::cout << "Wrong login or password" << std::endl;
        std::cout << "Please, try again" << std::endl;
        std::cout << "You can also add new user. Write 'add user'" << std::endl;
        std::cout << std::endl;
        return;
    }
}

void AccessProvider::logOut() {
    this->user->login_.clear();
    this->user->hashedPass_.clear();
    this->user->isLoggedIn_ = false;
    std::cout << "You've logged out" << std::endl;
}

void AccessProvider::changePassword() {

    std::string oldPassword;
    noechoInput(oldPassword, "\nPlease, enter old password: ");
    std::string hashedOldPassword = md5(oldPassword);

    auto userChecking = this->accountsDbManager->accountsDb->get_all<User>(where(is_equal(&User::login_, this->user->login_) &&
                                                                                 is_equal(&User::hashedPass_, hashedOldPassword)));

    if (!userChecking.empty()) {

        std::string newPasswordFirst;
        std::string newPasswordSecond;

        noechoInput(newPasswordFirst, "\n\nPlease, enter new password: ");
        noechoInput(newPasswordSecond, "\n\n\nPlease, enter new password again: ");

        if (!newPasswordFirst.compare(newPasswordSecond)) {

            this->user->hashedPass_ = md5(newPasswordFirst);
            this->accountsDbManager->accountsDb->remove<User>(this->user->id_);

            this->user->id_ = -1;
            auto insertedId = this->accountsDbManager->accountsDb->insert(*(this->user));
            this->user->id_ = insertedId;

            std::cout << "You've successfully change your password" << std::endl;
            newPasswordFirst.clear();
            newPasswordSecond.clear();
            this->logOut();

        } else {
            std::cout << "You've entered different passwords" << std::endl;
        }


    } else {
        std::cout << "You've entered wrong old password" << std::endl;
    }
    hashedOldPassword.clear();
}

//dialog between user and program
void AccessProvider::accessChecker(const std::string& arg1, const std::string& arg2) {
        if (!arg1.compare("log")) {
            if(!arg2.compare("in")) {
                this->logIn();
            } else {
                std::cout << "Wrong command. Please, check 'help'" << std::endl;
                std::cout << std::endl;
            }
        }

        else if (!arg1.compare("add")) {

            if (!arg2.compare("user")) {
                this->addingNewUser();
            } else {
                std::cout << "Wrong command. Please, check 'help'" << std::endl;
                std::cout << std::endl;
            }
        }

        else if(!arg1.compare("exit")) {
            exit(0);
        }

        else if(!arg1.compare("help")) {
            std::cout << "---List of supported commands before you log in---" << std::endl;

            std::cout << std::endl;

            std::cout << "add user  -allows to create new account"            << std::endl;
            std::cout << "log in    -allows to log in in account"             << std::endl;
            std::cout << "exit      -allow to close this app"                 << std::endl;

            std::cout << std::endl;
        }

        else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;
        }
}
