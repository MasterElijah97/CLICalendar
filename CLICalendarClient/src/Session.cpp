#include "Session.h"

Session::CopyableSetter::CopyableSetter(Session& sess) {
    this->session = &sess;
}
Session::CopyableSetter::~CopyableSetter() {
    this->session = nullptr;
}
void Session::CopyableSetter::operator()(std::vector<Deal>::iterator& it) {
	this->session->copyableObject_ = it;
	this->session->copyableSetted = DEAL_SETTED;
}
void Session::CopyableSetter::operator()(std::vector<Day>::iterator& it) {
	this->session->copyableObject_ = it;
	this->session->copyableSetted = DAY_SETTED;
}
void Session::CopyableSetter::operator()(std::vector<Task>::iterator& it) {
	this->session->copyableObject_ = it;
	this->session->copyableSetted = TASK_SETTED;
}
void Session::CopyableSetter::operator()(std::vector<Note>::iterator& it) {
	this->session->copyableObject_ = it;
	this->session->copyableSetted = NOTE_SETTED;
}
void Session::CopyableSetter::operator()(std::vector<Important>::iterator& it) {
	this->session->copyableObject_ = it;
	this->session->copyableSetted = IMPORTANT_SETTED;
}

Session::MoveableSetter::MoveableSetter(Session& sess) {
	this->session = &sess;
}
Session::MoveableSetter::~MoveableSetter() {
    this->session = nullptr;
}
void Session::MoveableSetter::operator()(std::vector<Deal>::iterator& it) {
	this->session->moveableObject_ = it;
	this->session->moveableSetted = DEAL_SETTED;
}
void Session::MoveableSetter::operator()(std::vector<Day>::iterator& it) {
	this->session->moveableObject_ = it;
	this->session->moveableSetted = DAY_SETTED;
}
void Session::MoveableSetter::operator()(std::vector<Task>::iterator& it) {
	this->session->moveableObject_ = it;
	this->session->moveableSetted = TASK_SETTED;
}
void Session::MoveableSetter::operator()(std::vector<Note>::iterator& it) {
	this->session->moveableObject_ = it;
	this->session->moveableSetted = NOTE_SETTED;
}
void Session::MoveableSetter::operator()(std::vector<Important>::iterator& it) {
	this->session->moveableObject_ = it;
	this->session->moveableSetted = IMPORTANT_SETTED;
}

template<typename T>
void Session::JoinedShower::operator()(T& it) {
	it->show();
}

Session::JoinedEditor::JoinedEditor(Session& sess) {
    this->session = &sess;
}
Session::JoinedEditor::~JoinedEditor() {
    this->session = nullptr;
}
template<typename T>
void Session::JoinedEditor::operator()(T& it) {
    it->edit();
    this->session->localDb->update(*it);
}
template<>
void Session::JoinedEditor::operator()<std::vector<Day>::iterator>(std::vector<Day>::iterator& it) {
    it->edit();

    std::string newdate_ = it->date_;

    if (!it->deals_.empty()) {
        for (auto &i : it->deals_) {
            i.date_ = newdate_;
            session->localDb->update(i);
        }
    }

    if (!(it->importants_.empty())) {
        for (auto &i : it->importants_) {
            i.date_ = newdate_;
            session->localDb->update(i);
        }
    }
    this->session->localDb->update(*it);
}


Session::CopyablePaster::CopyablePaster(Session& sess) {
    this->session = &sess;
}
Session::CopyablePaster::~CopyablePaster() {
    this->session = nullptr;
}
void Session::CopyablePaster::operator()(std::vector<Day>::iterator& copyable) {

    if(session->joinedSetted == DAY_SETTED &&
       session->copyableSetted == DAY_SETTED) {

        auto joined = std::get<std::vector<Day>::iterator>(this->session->joinedObject_);

        Day copyableItem = *(std::get<std::vector<Day>::iterator>(this->session->copyableObject_));

        copyableItem.id_ = -1;
        auto insertedId = this->session->localDb->insert(copyableItem);
        copyableItem.id_ = insertedId;

        this->session->days_.insert((joined + 1), copyableItem);

            for (auto it = (joined + 1); it <= (session->days_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
    }
}
void Session::CopyablePaster::operator()(std::vector<Task>::iterator& copyable) {

    if(session->joinedSetted == TASK_SETTED &&
       session->copyableSetted == TASK_SETTED) {

        auto joined = std::get<std::vector<Task>::iterator>(this->session->joinedObject_);

        Task copyableItem = *(std::get<std::vector<Task>::iterator>(this->session->copyableObject_));

        copyableItem.id_ = -1;
        auto insertedId = this->session->localDb->insert(*copyable);
        copyableItem.id_ = insertedId;

        this->session->tasks_.insert((joined + 1), *copyable);

            for (auto it = (joined + 1); it <= (session->tasks_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
    }
}

void Session::CopyablePaster::operator()(std::vector<Note>::iterator& copyable) {

    if(session->joinedSetted == NOTE_SETTED && session->copyableSetted == NOTE_SETTED) {

        auto joined = std::get<std::vector<Note>::iterator>(this->session->joinedObject_);

        Note copyableItem = *(std::get<std::vector<Note>::iterator>(this->session->copyableObject_));

        copyableItem.id_ = -1;
        auto insertedId = this->session->localDb->insert(*copyable);
        copyableItem.id_ = insertedId;

        this->session->notes_.insert((joined + 1), *copyable);

            for (auto it = (joined + 1); it <= (session->notes_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
    }
}

Session::MoveablePaster::MoveablePaster(Session& sess) {
    this->session = &sess;
}
Session::MoveablePaster::~MoveablePaster() {
    this->session = nullptr;
}
void Session::MoveablePaster::operator()(std::vector<Day>::iterator& copyable) {

    if( (session->joinedSetted   == DAY_SETTED) &&
        (session->moveableSetted == DAY_SETTED) &&
         session->days_.size() > 1) {

            auto joined = std::get<std::vector<Day>::iterator>(this->session->joinedObject_);
            auto moveable = std::get<std::vector<Day>::iterator>(this->session->moveableObject_);

            Day copyableItem = *(std::get<std::vector<Day>::iterator>(this->session->moveableObject_));

            session->days_.erase(moveable);
            session->localDb->remove<Day>(moveable->id_);

            copyableItem.id_ = -1;
            auto insertedId = this->session->localDb->insert(copyableItem);
            copyableItem.id_ = insertedId;

            this->session->days_.insert((joined), copyableItem);

            for (auto it = (joined); it <= (session->days_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
        std::cout << "or you are trying to process the only element" << std::endl;
    }
}
void Session::MoveablePaster::operator()(std::vector<Task>::iterator& copyable) {

    if( (session->joinedSetted == TASK_SETTED) &&
        (session->moveableSetted == TASK_SETTED) ) {

        auto joined = std::get<std::vector<Task>::iterator>(this->session->joinedObject_);

        Task copyableItem = *(std::get<std::vector<Task>::iterator>(this->session->moveableObject_));

        copyableItem.id_ = -1;
        auto insertedId = this->session->localDb->insert(*copyable);
        copyableItem.id_ = insertedId;

        this->session->tasks_.insert((joined), *copyable);

            for (auto it = (joined); it <= (session->tasks_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
    }
}

void Session:: MoveablePaster::operator()(std::vector<Note>::iterator& copyable) {

    if( (session->joinedSetted == NOTE_SETTED) &&
        (session->moveableSetted == NOTE_SETTED)) {

        auto joined = std::get<std::vector<Note>::iterator>(this->session->joinedObject_);

        Note copyableItem = *(std::get<std::vector<Note>::iterator>(this->session->moveableObject_));

        copyableItem.id_ = -1;
        auto insertedId = this->session->localDb->insert(*copyable);
        copyableItem.id_ = insertedId;

        this->session->notes_.insert((joined), *copyable);

            for (auto it = (joined); it <= (session->notes_.end()-2); ++it) {
                auto next = it + 1;
                if ( (it->id_) > (next->id_) ) {
                    std::swap<int>(it->id_, next->id_);
                    session->localDb->update(*it);
                    session->localDb->update(*next);
                }
            }

    } else {
        std::cout << "The types of the copied and the selected item do not match" << std::endl;
    }
}

Session::JoinedDecrementAllower::JoinedDecrementAllower(Session& sess) {
    this->session = &sess;
}
Session::JoinedDecrementAllower::~JoinedDecrementAllower() {
    this->session = nullptr;
}
void Session::JoinedDecrementAllower::operator()(std::vector<Day>::iterator& it) {
    if ( (it) != (session->days_.begin()) ) {
        it--;
    }
}
void Session::JoinedDecrementAllower::operator()(std::vector<Task>::iterator& it) {
    if ( (it) != (session->tasks_.begin()) ) {
        it--;
    }
}
void Session::JoinedDecrementAllower::operator()(std::vector<Note>::iterator& it) {
    if ( (it) != (session->notes_.begin()) ) {
        it--;
    }
}

Session::JoinedIncrementAllower::JoinedIncrementAllower(Session& sess) {
    this->session = &sess;
}
Session::JoinedIncrementAllower::~JoinedIncrementAllower() {
    this->session = nullptr;
}
void Session::JoinedIncrementAllower::operator()(std::vector<Day>::iterator& it) {
    if ( (it+1) != (session->days_.end()) ) {
        it++;
    }
}
void Session::JoinedIncrementAllower::operator()(std::vector<Task>::iterator& it) {
    if ( (it+1) != (session->tasks_.end()) ) {
        it++;
    }
}
void Session::JoinedIncrementAllower::operator()(std::vector<Note>::iterator& it) {
    if ( (it+1) != (session->notes_.end()) ) {
        it++;
    }
}

Session::Session(std::shared_ptr<User> user)
{
    this->user = std::move(user);
    this->databaseName = this->user->login_ + ".sqlite";
    this->localDb = std::make_shared<Storage>(initLocalDb(std::string(this->databaseName)));
    this->localDb->sync_schema();

	tasks_.reserve(100);
    notes_.reserve(1000);
    days_.reserve(3000);

    this->getDataFromLocalBase();
}

//public

void Session::getDataFromLocalBase() {
	try {
        this->tasks_ = localDb->get_all<Task>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Tasks::Something went wrong" << std::endl;
	}


	try {
    	this->notes_ = localDb->get_all<Note>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one note found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Notes::Something went wrong" << std::endl;
	}

	try {
    	this->days_ = localDb->get_all<Day>();
	}
	catch (sqlite_orm::orm_error_code) {
      	std::cout << "No one day found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Days::Something went wrong" << std::endl;
	}

	for (auto it = days_.begin(); it != days_.end(); ++it) {
    	try {
        	it->deals_ = localDb->get_all<Deal>(where(is_equal(&Deal::date_, it->date_)));
    	}
    	catch(sqlite_orm::orm_error_code) {
        	continue;
    	}
    	catch(...) {
        	std::cout << std::setw(24) << "Deals::Something went wrong" << std::endl;
    	}

        try {
            it->importants_ = localDb->get_all<Important>(where(is_equal(&Important::date_, it->date_)));
        }
        catch(sqlite_orm::orm_error_code) {
            continue;
        }
        catch(...) {
            std::cout << std::setw(24) << "Importants::Something went wrong" << std::endl;
        }
	}
}

void Session::creatingTask() {
    std::string description;
    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, description, '\n');
    std::cout << std::endl;

    Task task(description);
    auto insertedId = localDb->insert(task);
    task.id_= insertedId;
    tasks_.push_back(task);

    std::cout << "New task has been created :)" << std::endl;
    std::cout << std::endl;
}
void Session::creatingNote() {
    std::string name;
    std::string description;
    std::string label;

    std::cout << std::setw(13) << "Name: ";
    std::getline(std::cin, name, '\n');
    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, description, '\n');
    std::cout << std::setw(13) << "Label: ";
    std::getline(std::cin, label, '\n');
    std::cout << std::endl;
    Note note(name, description, label);

    auto insertedId = localDb->insert(note);
    note.id_= insertedId;
    notes_.push_back(note);

    std::cout << "New note has been created :)" << std::endl;
    std::cout << std::endl;
}

void Session::creatingDay() {
    std::string date;
    std::cout << "Date (YYYYMMDD): ";
    std::getline(std::cin, date, '\n');
    std::cout << std::endl;

    Day day(date);

    auto insertedId = localDb->insert(day);
    day.id_= insertedId;

    days_.push_back(day);

    auto it = this->days_.end() - 1;
    this->setJoined(it);
    //checks for stolen deals
    it->deals_ = this->localDb->get_all<Deal>(where(is_equal(&Deal::date_, it->date_)));
    it->importants_ = this->localDb->get_all<Important>(where(is_equal(&Important::date_, it->date_)));

    std::cout << "New day has been created :)" << std::endl;
    std::cout << std::endl;
}

void Session::creatingDeal() {

    if(this->joinedSetted == 1) {


        std::string name;
        std::string description;
        std::string label;
        std::string priority;
        std::string begins;
        std::string ends;

        std::cout << std::setw(20) << "Name: ";
        std::getline(std::cin, name, '\n');
        std::cout << std::setw(20) << "Description: ";
        std::getline(std::cin, description, '\n');
        std::cout << std::setw(20) << "Label: ";
        std::getline(std::cin, label, '\n');
        std::cout << std::setw(20) << "Priority: ";
        std::getline(std::cin, priority, '\n');
        std::cout << std::setw(20) << "Begins at: ";
        std::getline(std::cin, begins, '\n');
        std::cout << std::setw(20) << "Ends at: ";
        std::getline(std::cin, ends, '\n');
        std::cout << std::endl;

        Deal deal(name,
                  description,
                  label,
                  priority,
                  begins,
                  ends);

    std::string date = std::get<std::vector<Day>::iterator>(joinedObject_)->date_;
    deal.setDate(date);

    auto insertedId = localDb->insert(deal);
    deal.id_= insertedId;
    std::get<std::vector<Day>::iterator>(joinedObject_)->addDeal(deal);


    std::cout << "New deal has been created :)" << std::endl;
    std::cout << std::endl;

    } else {

        std::cout << "Please, open day and chose the one where you want to create deal" << std::endl;
        std::cout << std::endl;

    }

}

void Session::creatingImportant() {

    if (this->joinedSetted == 1) {

        std::string tmp;
        std::cout << std::setw(13) << "Important: ";
        std::getline(std::cin, tmp, '\n');
        std::cout << std::endl;
        Important important(tmp);
        important.date_ = std::get<std::vector<Day>::iterator>(joinedObject_)->date_;

        auto insertedId = localDb->insert(important);
        important.id_ = insertedId;
        std::get<std::vector<Day>::iterator>(joinedObject_)->addImportant(important);


        std::cout << "New important has been created :)" << std::endl;
        std::cout << std::endl;

    } else {
        std::cout << "Please, open day and chose the one where you want to create important" << std::endl;
        std::cout << std::endl;
    }
}

 void Session::addTask(Task task) {
     this->tasks_.emplace_back(std::move(task));
 }

 void Session::addNote(Note note) {
     this->notes_.emplace_back(std::move(note));
 }

 void Session::addDay(Day day) {
     this->days_.emplace_back(std::move(day));
 }

 void Session::openTasks() {

    if (!this->tasks_.empty()) {

        auto it = this->tasks_.end() - 1;
        this->setJoined(it);
        this->joinedSetted = this->variantObserver::TASK_SETTED;
        std::visit(Session::JoinedShower{}, this->joinedObject_);

    } else {
        std::cout << "There is no one task" << std::endl;
    }
}

void Session::openNotes() {

    if (!this->notes_.empty()) {

        auto it = this->notes_.end() - 1;
        this->setJoined(it);
        this->joinedSetted = this->variantObserver::NOTE_SETTED;
        std::visit(Session::JoinedShower{}, this->joinedObject_);

    } else {
        std::cout << "There is no one note" << std::endl;
    }
}

void Session::openDays() {

    if (!this->days_.empty()) {

        auto it = this->days_.end() - 1;
        this->setJoined(it);
        this->joinedSetted = this->variantObserver::DAY_SETTED;;

        std::visit(Session::JoinedShower{}, this->joinedObject_);

    } else {
        std::cout << "There is no one day" << std::endl;
    }
}

 void Session::showJoined() {
 	std::visit(JoinedShower{}, this->joinedObject_);
 }
 void Session::showHelp() {
 	std::cout << "---List of supported commands---"                                                                      << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Navigation--"                                                                                        << std::endl;
 	std::cout << "next                                -allows to get next item"                                          << std::endl;
 	std::cout << "prev                                -allows to get previous item"                                      << std::endl;

    std::cout << std::endl;

 	std::cout << "--Manipulating with data--"                                                                            << std::endl;
 	std::cout << "open tasks/notes/days               -open tasks or notes or days and join it"                          << std::endl;
 	std::cout << "create task/note/day/deal/important -create task or note or day or deal"                               << std::endl;
 	std::cout << "edit                                -allows to edit joined item"                                       << std::endl;
 	std::cout << "copy                                -allows to copy joined item (works in pair with command \"paste\"" << std::endl;
 	std::cout << "past                                -allows to copy joined item (works in pair with command \"copy\""  << std::endl;
 	std::cout << "move                                -allows to move joined item (works in pair with command \"here\""  << std::endl;
 	std::cout << "here                                -allows to move joined item (works in pair with command \"move\""  << std::endl;
 	std::cout << "------------------------------------------------------------------------------"                        << std::endl;
 	std::cout << "|Commands 'paste' and 'here' pastes copyable/moveable item before joined item|"                        << std::endl;
 	std::cout << "------------------------------------------------------------------------------"                        << std::endl;
 	std::cout << "remove task/note/day                -removes joined task/note/day"                                     << std::endl;
 	std::cout << "If day is opened: "                                                                                    << std::endl;
 	std::cout << "edit deal/important N               -allows to edit deal/important with number N"                      << std::endl;
 	std::cout << "remove deal/important N             -removes deal/important with number N"                             << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Manipulating with accounts--"                                                                        << std::endl;
 	std::cout << "log out                   -allows to log out from  account"                                            << std::endl;
 	std::cout << "change password           -allows to change password"                                                  << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Manipulating with server--"                                                                          << std::endl;
 	std::cout << "connect                   -allows to connect to server"                                                << std::endl;
 	std::cout << "disconnect                -allows to disconnect from server"                                           << std::endl;
 	std::cout << "sync                      -synchronises local and server databases"                                    << std::endl;

    std::cout << "HOW TO BACK UP YOUR DATABASE IF SOMETHING WENT WRONG AFTER 'sync' COMMAND"                                        << std::endl;
 	std::cout << "1. Go to 'backup' directory that will apear after first usage of 'sync' command and copy %yourlogin%.sqlite file" << std::endl;
 	std::cout << "2. Relace %yourlogin%.sqlite file with %yourlogin%.sqlite file from 'backup' directory"                           << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Other--"                                                                                             << std::endl;
 	std::cout << "exit                      -sync bases, disconnect from server and log out"                             << std::endl;

 	std::cout << std::endl;
 }

 void Session::editDeal(std::size_t arg3) {

    if(this->joinedSetted == 1 &&  (arg3-1) > 0) {

        auto it = std::get<std::vector<Day>::iterator>(this->joinedObject_);
        if ( (arg3-1) < (it->deals_.size()) )  {
            it->deals_[arg3-1].edit();
        } else {
            std::cout << "There is no such deal" << std::endl;
        }

    } else {
        std::cout << "Please, open days and chose day you need" << std::endl;
    }
}

void Session::editImportant(std::size_t arg3) {
    if( (this->joinedSetted == 1) && (arg3-1) > 0) {

        auto it = std::get<std::vector<Day>::iterator>(this->joinedObject_);
        if ( (arg3-1) < (it->importants_.size()) )  {
            it->importants_[arg3-1].edit();
        } else {
            std::cout << "There is no such important" << std::endl;
        }

    } else {
        std::cout << "Please, open days and chose day you need" << std::endl;
    }
}

void Session::editItem() {

    if ( this->joinedSetted != 0 ) {

        std::visit(Session::JoinedEditor{*this}, this->joinedObject_);

    } else {
        std::cout << "Please, open  days/tasks/notes and chose the item you want to edit" << std::endl;
    }
}

void Session::copyItem() {

    if ( this->joinedSetted != 0 ) {

        std::visit(Session::CopyableSetter{*this}, this->joinedObject_);

    } else {
        std::cout << "Please, open  days/tasks/notes and chose the item you want to copy" << std::endl;
    }
}

void Session::pasteItem() {

    if ( (this->joinedSetted != 0) && (this->copyableSetted != 0) ) {

        std::visit(Session::CopyablePaster{*this}, this->copyableObject_);

    } else {
        std::cout << "Something went wrong" << std::endl;
        std::cout << "Please, chose item to copy and then chose item to paste" << std::endl;
    }
}

void Session::moveItem() {

    if ( this->joinedSetted != 0 ) {

        std::visit(Session::MoveableSetter{*this}, this->joinedObject_);

    } else {
        std::cout << "Please, open  days/tasks/notes and chose the item you want to copy" << std::endl;
    }
}

void Session::pasteMoveableItem() {

    if ( (this->joinedSetted != 0)   &&
         (this->moveableSetted != 0) &&
         (this->joinedSetted == this->moveableSetted) ) {

        std::visit(Session::MoveablePaster{*this}, this->moveableObject_);

    } else {
        std::cout << "Something went wrong" << std::endl;
        std::cout << "Please, chose item to copy and then chose item to paste" << std::endl;
    }
}

void Session::removeTask() {

    if ( (this->joinedSetted == 3) &&
         (!this->tasks_.empty()) ) {

        auto it = std::get<std::vector<Task>::iterator>(this->joinedObject_);

        this->localDb->remove<Task>(it->id_);
        this->tasks_.erase(it);

    } else {
        std::cout << "Please, open tasks and chose task you need to remove" << std::endl;
    }
}

void Session::removeNote() {

    if ( (this->joinedSetted == 2) &&
         (!this->notes_.empty()) ) {

        auto it = std::get<std::vector<Note>::iterator>(this->joinedObject_);

        this->localDb->remove<Note>(it->id_);
        this->notes_.erase(it);

    } else {
        std::cout << "Please, open notes and chose note you need to remove" << std::endl;
    }
}

void Session::removeDay() {

    if ( (this->joinedSetted == 1) &&
         (!this->days_.empty()) ) {

        auto it = std::get<std::vector<Day>::iterator>(this->joinedObject_);
        this->localDb->remove<Day>(it->id_);
        this->days_.erase(it);

    } else {
        std::cout << "Please, open days and chose day you need to remove" << std::endl;
    }

}

void Session::removeDeal(std::size_t arg3) {

    if ( (this->joinedSetted == 1) &&
         (!this->days_.empty()) ) {

        auto it = std::get<std::vector<Day>::iterator>(this->joinedObject_);

        if (!it->deals_.empty()) {

            if (arg3 <= (it->deals_.size())) {

                this->localDb->remove<Deal>(it->deals_[arg3-1].id_);
                it->removeDeal(arg3);

            } else {
                std::cout << "There is no such deal" << std::endl;
            }
        } else {
            std::cout << "There is no one deal" << std::endl;
        }
    } else {
        std::cout << "Please open days and chose day from  what you want remove the deal" << std::endl;
    }
}

void Session::removeImportant(std::size_t arg3) {

    if ( (this->joinedSetted == 1) &&
         (!this->days_.empty()) ) {

        auto it = std::get<std::vector<Day>::iterator>(this->joinedObject_);

        if (!it->importants_.empty()){

            if (arg3 <= (it->importants_.size())) {

                this->localDb->remove<Important>(it->importants_[arg3-1].id_);
                it->removeImportant(arg3);

            } else {
                std::cout << "There is no such important" << std::endl;
            }
        } else {
            std::cout << "There is no one important" << std::endl;
        }
    } else {
        std::cout << "Please open days and chose day from  what you want remove the important" << std::endl;
    }

}

template<typename T>
void Session::setJoined(T it) {
	joinedObject_ = std::move(it);
}

/*void Session::setJoined(std::vector<Day>::iterator it) {
   this->joinedObject_ = std::move(it);
}
void Session::setJoined(std::vector<Deal>::iterator it) {
   this->joinedObject_ = std::move(it);
}
void Session::setJoined(std::vector<Task>::iterator it) {
   this->joinedObject_ = std::move(it);
}
void Session::setJoined(std::vector<Note>::iterator it) {
   this->joinedObject_ = std::move(it);
}
void Session::setJoined(std::vector<Important>::iterator it) {
   this->joinedObject_ = std::move(it);
}*/


void Session::incrementJoined() {

		if( (this->joinedSetted != 0) &&
            (std::holds_alternative<std::vector<Day>::iterator>(this->joinedObject_) ||
             std::holds_alternative<std::vector<Task>::iterator>(this->joinedObject_) ||
             std::holds_alternative<std::vector<Note>::iterator>(this->joinedObject_)) ) {

            std::visit(Session::JoinedIncrementAllower{*this}, this->joinedObject_);
            std::visit(Session::JoinedShower{}, this->joinedObject_);

        } else {
            std::cout << "Please, open tasks or notes or deal" << std::endl;
        }

}

void Session::decrementJoined() {

        if( (this->joinedSetted != 0) &&
            (std::holds_alternative<std::vector<Day>::iterator>(this->joinedObject_) ||
            std::holds_alternative<std::vector<Task>::iterator>(this->joinedObject_) ||
            std::holds_alternative<std::vector<Note>::iterator>(this->joinedObject_))
            ) {

            std::visit(Session::JoinedDecrementAllower{*this}, this->joinedObject_);
            std::visit(Session::JoinedShower{}, this->joinedObject_);

        } else {
            std::cout << "Please, open tasks or notes or deal" << std::endl;
        }

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
void Session::setMovable() {
    std::visit(MoveableSetter{*this}, this->joinedObject_);
}

void Session::setCopyable() {
    std::visit(CopyableSetter{*this}, this->joinedObject_);
}
