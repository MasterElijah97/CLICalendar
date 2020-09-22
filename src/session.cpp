#include "session.h"

//private

Session::Session(const Session&) {

}
Session::Session(Session&&) {

}
Session& Session::operator=(const Session&) {

}
Session& Session::operator=(Session&&) {

}

Session::Session()
{
	tasks_.reserve(100);
    notes_.reserve(1000);
    days_.reserve(3000);
}

void Session::addingNewUser() {
    std::string login;
    std::string password;
    std::cout << "Please, enter new login" << std::endl;
    std::cin >> login;

    auto user = accountsDb.get_no_throw<User>(where(is_equal(&User::login_, login)))

    if (!user) {
        std::cout << "Please, enter new password" << std::endl;
        std::cin >> password;

        this->user.login_ = login;
        this->user.hashedPass_ = md5(password);

        auto insertedId = accountsDb.insert(this->user);
        this->user.id_ = insertedId;

        std::cout << "New account has been created" << std::endl;
        std::cout << "Now you can log in with entered login and password" << std:: endl;
    } else {
        std::cout << "Sorry, this login is exists. Please, try again." << std::endl;
    }
}

void Session::setLoginAndPassword(const std::string& login, const std::string& password) {
	this->user.login_ = login;
	this->user.hashedPass_ = password;
}

//public

Session& Session::instance() {
    static std::unique_ptr<Session> instance(new Session());
    return *instance;
}

void Session::logIn() {

    std::string login;
    std::string password;
    std::string hashedPassword;

    std::cout << "Login:";
    std::cin >> login;
    std::cout << std::endl;

    std::cout << "Password";
    std::cin >> password;
    std::cout << std::endl;
    hashedPassword = md5(password);

    auto ExistingUser = storage.get_no_throw<User>(where(is_equal(&User::login_, login) && 
                                                    is_equal(&User:hashedPass_, hashedPassword)));

    if (ExistingUser) {
		this->setLoginAndPassword(login, hashedPassword);
        std::cout << "You've succesfully logged in" << std::endl;
        this->user.isLoggedIn_ = true;
        this->initDatabases(login);
    else {
        std::cout << "Wrong login or password" << std::endl;
        std::cout << "Please, try again" << std::endl;
    }
}

void Session::logOut() {
            //todo
            this->user.login_.clear();
            this->user.hashedPass_.clear();
            this->user.isLoggedIn_ = false;

            tasksDb = nullptr;
            notesDb = nullptr;
            daysDb = nullptr;
            dealsDb = nullptr;

            //this->//disconnect from db by
            //this->//disconnect from server if connected

}


void getDataFromLocalBase() {
	try {
		tasks_ = storage.get_all<Task>;
	}
	catch (sqlite_orm::not_found_exception) {
    	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}	


	try {
    	notes_ = storage.get_all<Note>;
	}
	catch (sqlite_orm::not_found_exception) {
    	std::cout << "No one note found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}	

	try {
    	days_ = storage.get_all<Day>;
	}
	catch (sqlite_orm::not_found_exception) {
      	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}

	for (auto it = days_.begin(); it != days_.end(); ++it) {
    	try {
        	it->deals_ = storage.get_all<Deal>(where(is_equal(&Deal::date_, it->getDate())));
    	}
    	catch(sqlite_orm::not_found_exception) {
        	continue;
    	}
    	catch(...) {
        	std::cout << "Unknown exception" << std::endl;
    	}
	}
}

void Session::creatingTask() {
    std::string description;
    std::cout << "Please, enter description" << std::endl;
    std::cin >> description;
    tasks_.emplace_back(Task(description));
}
void Session::creatingNote() {
    std::string name;
    std::string description;
    std::string label;

    std::cout << "Please, enter name" << std::endl;
    std::cin >> name;
    std::cout << "Please, enter description" << std::endl;
    std::cin >> description;
    std::cout << "Please, enter label" << std::endl;
    std::cin >> label;
    notes_.emplace_back(Note(name, description, label));
}

void Session::creatingDay() {
    std::string date;
    std::cout << "Please, enter date in format DDMMYYYY" << std::endl;
    std::cin >> date;
    days_.emplace_back(Day(date));
}

void Session::creatingDeal() {
    std::string name;
    std::string description;
    std::string label;
    std::string priority;
    std::string time;

    std::cout << "Please, enter name" << std::endl;
    std::cin >> name;
    std::cout << "Please, enter description" << std::endl;
    std::cin >> description;
    std::cout << "Please, enter label" << std::endl;
    std::cin >> label;
    std::cout << "Please, enter priority" << std::endl;
    std::cin >> priority;
    std::cout << "Please, enter time in format HH:MM-HH::MM" << std::endl;
    std::cin >> time;
    Deal newDeal(name,
                description,
                label,
                priority,
                time.substr(0, 2)+time.substr(4, 5),
                time.substr(7, 9)+time.substr(11, 12));
    joinedObject_->addDeal(newDeal);
}


void Session::connectToServer() {
            //todo
}

void Session::disconnectFromServer() {
	//todo
}

void Session::getTasksFromServer() {
	//getting info

}

void Session::getNotesFromServer() {
     //getting info

 }

 void Session::getDaysFromServer() {
     //getting info

 }

 void Session::connectToLocalBase() {

 }

 void Session::syncWithLocalBase() {
     //syncDays
     //syncDeals
     //syncNotes
     //syncTasks
     //sync into tmp variable
     //clear old version after complete
 }

 void Session::syncWithServerBase() {
     //sending a lot of data by protocol
     //syncDays
     //syncDeals
     //syncNotes
     //syncTasks
     //sync into tmp variable
     //clear old version after complete
 }

 void Session::syncBases() {
     this->syncWithLocalBase();
     this->syncWithServerBase();
 }

void Session::getTasks() const {
	return tasks_;
};
void Session::getNotes() const {
	return notes_;
};
void Session::getDays() const {
	return days_;
};

 void Session::addTask(Task task) {
     this->tasks.push_back(task);
 }

 void Session::addNote(Note note) {
     this->notes.push_back(note);
 }

 void Session::addDay(Day day) {
     this->tasks.push_back(day);
 }

 void Session::showJoined() {
 	this->joinedObject_->show();
 }
 void Session::showHelp() {
 	std::cout << "---List of supported commands---"                                                            << std::endl;

 	std::cout << std::endl;
 	std::cout << "--Navigation--"                                                                              << std::endl;
 	std::cout << "next                      -allows to get next item"                                          << std::endl;
 	std::cout << "prev                      -allows to get previous item"                                      << std::endl;
 	
 	std::cout << "--Manipulating with data--"                                                                  << std::endl;
 	std::cout << "open tasks/notes/days     -open tasks or notes or days"                                      << std::endl;
 	std::cout << "create task/note/day/deal -create task or note or day or deal"                               << std::endl;
 	std::cout << "join deals                -allows to manipulate with deals if day is chosen"                 << std::endl;
 	std::cout << "edit                      -allows to edit joined item"                                       << std::endl;
 	std::cout << "copy                      -allows to copy joined item (works in pair with command \"paste\"" << std::endl;
 	std::cout << "past                      -allows to copy joined item (works in pair with command \"copy\""  << std::endl;
 	std::cout << "remove task/note/day      -removes task/note/day"                                            << std::endl;
 	std::cout << "remove deal/important N   -removes deal/important with number N"                             << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Manipulating with accounts--"                                                              << std::endl;
 	std::cout << "add user                  -allows to create new account"                                     << std::endl;
 	std::cout << "login                     -allows to login in account"                                       << std::endl;
 	std::cout << "logout                    -allows to logout from  account"                                   << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Manipulating with server--"                                                                << std::endl;
 	std::cout << "connect                   -allows to connect to server"                                      << std::endl;
 	std::cout << "disconnect                -allows to disconnect from server"                                 << std::endl;
 	std::cout << "sync                      -synchronises local and server databases"                          << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Other--"                                                                                   << std::endl;
 	std::cout << "exit                      -sync bases, disconnect from server and logout"                    << std::endl;
 }
 //getters

 //setters

 std::variant<
    std::vector<Day>::iterator,
    std::vector<Note>::iterator,
    std::vector<Task>::iterator,
    std::vector<Deal>::iterator
> Session::getJoined() const {
    return joinedObject_;
};


std::variant<
    std::vector<Day>::iterator,
    std::vector<Note>::iterator,
    std::vector<Task>::iterator,
    std::vector<Deal>::iterator
> Session::getCopyable() const {
    return copyableObject_;
};

std::variant<
    std::vector<Day>::iterator,
    std::vector<Note>::iterator,
    std::vector<Task>::iterator,
    std::vector<Deal>::iterator
> Session::getMoveable() const {
    return moveableObject_;
};

/*
template<typename T>
void Session::setJoined(std::vector<T>::iterator it) {
	joinedObject_ = it;
}
*/
void Session::setJoined(std::vector<Day>::iterator it) {
   joinedObject_ = it;
}
void Session::setJoined(std::vector<Deal>::iterator it) {
   joinedObject_ = it;
}
void Session::setJoined(std::vector<Task>::iterator it) {   
   joinedObject_ = it;
}
void Session::setJoined(std::vector<Note>::iterator it) {   
   joinedObject_ = it;
}

void Session::incrementJoined() {
	this->joinedObject_ = joinedObject_ + 1;	
}

void Session::decrementJoined() {
	this->joinedObject_ = joinedObject_ + 1;
}

/*
template<typename T>
void Session::setMovable(std::vector<T>::iterator it) {
	movableObject_ = it;
}

template<typename T>
void Session::setCopyable(std::vector<T>::iterator it) {
	copyableObject_ = it;
}
*/
void Session::setMovable(std::vector<Day>::iterator it) {
    moveableObject_ = it;
}
void Session::setMovable(std::vector<Deal>::iterator it) {
    moveableObject_ = it;
}
void Session::setMovable(std::vector<Task>::iterator it) {
    moveableObject_ = it;
}
void Session::setMovable(std::vector<Note>::iterator it) {
    moveableObject_ = it;
}

void Session::setCopyable(std::vector<Day>::iterator it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Deal>::iterator it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Task>::iterator it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Note>::iterator it) {
    copyableObject_ = it;
}

//refactoring needs
//need visit in runtime!!!
void Session::setJoinedLabel(const std::string msg) {
	std::visit(JoinedLabelSetter{std::move(msg)}, joinedObject_);
}
void Session::setJoinedName(const std::string msg) {
	std::visit(JoinedNameSetter{std::move(msg)}, joinedObject_);
}
void Session::setJoinedDescription(const std::string msg) {
	std::visit(JoinedDescriptionSetter{std::move(msg)}, joinedObject_);
}
void Session::setJoinedPriority(const std::string msg) {
	std::visit(JoinedPrioritySetter{std::move(msg)}, joinedObject_); 
}
void Session::setJoinedTime(const std::string msg) {
	std::visit(JoinedTimeSetter{std::move(msg)}, joinedObject_);
}
void Session::setJoinedComplited(const bool complited) {
    std::visit(JoinedComplitedSetter{std::move(msg)}, joinedObject_);
}
void Session::setJoinedDate(const std::string msg) {
	std::visit(JoinedDateSetter{std::move(msg)}, joinedObject_);
}

void Session::eraseDealFromJoined(int& pos) {
    (std::get<std::vector<Day>::iterator>(joinedObject_))->removeDeal(pos);
}
void Session::eraseImportantFromJoined(int& pos) {
    (std::get<std::vector<Day>::iterator>(joinedObject_))->removeImportant(pos);
}

void Session::eraseJoinedTask() {
    tasks_.erase(std::get<std::vector<Task>::iterator>(joinedObject_));
}
void Session::eraseJoinedNote() {
    note_.erase(std::get<std::vector<Note>::iterator>(joinedObject_));
}
void Session::eraseJoinedDay() {
    days_.erase(std::get<std::vector<Day>::iterator>(joinedObject_));
}