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

void Session::setLoginAndPassword(std::string& login, std::string& password) {
	this->login_ = login;
	this->password = password_;
}

//public

Session& Session::instance() {
    static std::unique_ptr<Session> instance(new Session());
    return *instance;
}

void Session::logIn(const std::string& login, const std::string& password) {
	if (MD5(password) == storage.get<Account>(where(is_equal(&Password::login_, login))); {
		this->setLoginAndPassword();
        std::cout << "You've succesfully logged in" << std::endl;
    else {
        std::cout << "Wrong login or password" << std::endl;
    }

    
   	//todo
    //match with local db
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
    notes_.emplace_back(Note(name,
                            description,
                            label,
                            priority,
                            time.substr(0, 2)+time.substr(4, 5),
                            time.substr(7, 9)+time.substr(11, 12)));
}

void Session::logOut() {
            //todo
            login_.clear();
            password_.clear();
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

 void Session::addTask(Task task) {
     this->tasks.emplace_back(task);
 }

 void Session::addNote(Note note) {
     this->notes.emplace_back(note);
 }

 void Session::addDay(Day day) {
     this->tasks.emplace_back(day);
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