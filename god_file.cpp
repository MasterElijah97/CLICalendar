#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <variant>

#include "include/sqlite_orm.h"
#include "include/MD5.h"

const std::string SEPARATOR(3, '&');

class Deal {
    public:
    int id_;
    int version_;
    void updateVersion() {
        this->version_++;
    }
        //constructors
        Deal();

        Deal(std::string,
             std::string,
             std::string,
             std::string,
             std::string,
             std::string);

        Deal(const Deal&);

        Deal(Deal&&);
        //operators
        friend bool operator==(const Deal& left, const Deal& right);

        Deal& operator=(const Deal&);

        Deal& operator=(Deal&&);
        //destructor
        ~Deal() = default;
        //clearing
        void clearName();
        void clearDescription();
        void clearLabel();
        void clearPriority();
        void clearTime();
        //getters

        //setters

        void setName(std::string);
        void setDescription(std::string);
        void setLabel(std::string);
        void setPriority(std::string);
        void setTime(std::string, std::string);
        void setDate(std::string);

        void edit();

        void show();

        std::string concatenate();

        void deconcatenate(std::string&);

        std::string name_;
        std::string description_;
        std::string label_;
        std::string priority_;
        std::string date_;
        struct Time {
            std::string begin_;
            std::string end_;
        } thisTime;
};

bool operator==(const Deal& left, const Deal& right) {
    return (left.name_          == right.name_)          &&
           (left.description_   == right.description_)   &&
           (left.label_         == right.label_)         &&
           (left.priority_      == right.priority_)      &&
           (left.thisTime.begin_ == right.thisTime.begin_) &&
           (left.thisTime.end_   == right.thisTime.end_)   &&
           (left.version_       == right.version_);
}

Deal::Deal() {
    description_ = "New Deal";
    name_ = "New Deal";
    label_ = "My Deals";
    priority_ = "A";
    thisTime.begin_ = "0000";
    thisTime.end_ = "0100";
}

Deal::Deal(std::string name,
     std::string description = "No description",
     std::string label = "My Deals",
     std::string priority = "A",
     std::string begins = "0000",
     std::string ends = "0000") {
    name_ = std::move(name);
    description_ = std::move(description);
    label_ = std::move(label);
    priority_ = std::move(priority);
    thisTime.begin_ = std::move(begins);
    thisTime.end_ = std::move(ends);
}

Deal::Deal(const Deal& other) {
    name_ = other.name_;
    description_ = other.description_;
    label_ = other.label_;
    priority_ = other.priority_;
    thisTime.begin_ = other.thisTime.begin_;
    thisTime.end_ = other.thisTime.end_;
    version_ = other.version_;
}

Deal::Deal(Deal&& other) {
    name_ = other.name_;
    description_ = other.description_;
    label_ = other.label_;
    priority_ = other.priority_;
    thisTime.begin_ = other.thisTime.begin_;
    thisTime.end_ = other.thisTime.end_;
    version_ = other.version_;

    other.clearName();
    other.clearDescription();
    other.clearLabel();
    other.clearPriority();
    other.clearTime();
}
//operators

Deal& Deal::operator=(const Deal& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.name_;
    description_ = other.description_;
    label_ = other.label_;
    priority_ = other.priority_;
    thisTime.begin_ = other.thisTime.begin_;
    thisTime.end_ = other.thisTime.end_;
    version_ = other.version_;

    return *this;
}

Deal& Deal::operator=(Deal&& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.name_;
    description_ = other.description_;
    label_ = other.label_;
    priority_ = other.priority_;
    thisTime.begin_ = other.thisTime.begin_;
    thisTime.end_ = other.thisTime.end_;
    version_ = other.version_;

    other.clearName();
    other.clearDescription();
    other.clearLabel();
    other.clearPriority();
    other.clearTime();

    return *this;
}
//clearing
void Deal::clearName() {
    name_.clear();
}

void Deal::clearDescription() {
    description_.clear();
}

void Deal::clearLabel() {
    label_.clear();
}

void Deal::clearPriority() {
    priority_.clear();
}

void Deal::clearTime() {
    thisTime.begin_.clear();
    thisTime.end_.clear();
}
//getters

//setters

void Deal::setName(std::string name) {
    name_ = std::move(name);
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setDescription(std::string description) {
    description_ = std::move(description);
    updateVersion();
    //base_->update(*this);
}

void Deal::setLabel(std::string label) {
    label_ = std::move(label);
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setPriority(std::string priority) {
    priority_ = std::move(priority);
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setTime(std::string begins, std::string ends) {
    thisTime.begin_ = std::move(begins);
    thisTime.end_ = std::move(ends);
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setDate(std::string date) {
    this->date_ = std::move(date);
    this->updateVersion();
    //base_->update(*this);
}

void Deal::show() {
    //todo formatting time
    std::cout << thisTime.begin_.substr(0, 1) << ":" << thisTime.begin_.substr(3, 4)
              << "-"
              << thisTime.end_.substr(0, 1)  << ":" << thisTime.end_.substr(3, 4)
              << std::endl;
    std::cout << "#" << label_ << std::endl;
    std::cout << priority_ << std::endl;
    std::cout << name_ << std::endl;
    std::cout << description_ << std::endl;
}

void Deal::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Name: ";
    std::cin >> input;
    if (!input.empty()) {
        this->name_ = input;
        input.clear();
    }

    std::cout << "Description: ";
    std::cin >> input;
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }

    std::cout << "Label: ";
    std::cin >> input;
    if (!input.empty()) {
        this->label_ = input;
        input.clear();
    }

    std::cout << "Priority: ";
    std::cin >> input;
    if (!input.empty()) {
        this->priority_ = input;
        input.clear();
    }

    std::cout << "Begins at ";
    std::cin >> input;
    if (!input.empty()) {
        this->thisTime.begin_ = input;
        input.clear();
    }

    std::cout << "Ends at ";
    std::cin >> input;
    if (!input.empty()) {
        this->thisTime.end_ = input;
        input.clear();
    }

    std::cout << std::endl;
    this->updateVersion();
//    base_->update(*this);
}

std::string Deal::concatenate() {
    return thisTime.begin_            +SEPARATOR+
           thisTime.end_              +SEPARATOR+
           name_                     +SEPARATOR+
           label_                    +SEPARATOR+
           priority_                 +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_) +SEPARATOR+
           description_;
}

void Deal::deconcatenate(std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;

    for (std::size_t i = 0; i != msg.size(); ++i) {

        if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
                thisTime.begin_ = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 1) {
                counter++;
                thisTime.end_ = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 2) {
                counter++;
                name_ = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 3) {
            	counter++;
                label_ = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 4) {
                counter++;
                priority_ = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 5) {
                counter++;
                version_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+3;
            } else if (counter == 6) {
                counter++;
                id_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+3;
            }
        }
    }
    description_ = msg.substr(posBegin);
}

class Important
{
public:
    int id_;
    int version_;
    void updateVersion() {
        this->version_++;
    }
    Important() = default;
    Important(std::string);
    Important(const Important&);
    Important(Important&&);
    Important& operator=(const Important&);
    Important& operator=(Important&&);

    std::string important_;

    std::string getImportant() const;
    void setImportant(std::string);

};

bool operator==(const Important& left, const Important& right) {
    return left.important_ == right.important_;
}

Important::Important(std::string important) {
    this->important_ = important;
}
Important::Important(const Important& other) {
	this->important_ = other.important_;
}
Important::Important(Important&& other) {
	this->important_ = other.important_;
}
Important& Important::operator=(const Important& other) {
	if (this == &other) {
        return *this;
    }
	this->important_ = other.important_;
	return *this;

}
Important& Important::operator=(Important&& other) {
	if (this == &other) {
        return *this;
    }
	this->important_ = other.important_;
	return *this;
}

std::string Important::getImportant() const {
    return this->important_;
}
void Important::setImportant(std::string msg) {
	this->important_ = std::move(msg);
	//base_->insert(*this);
}

class Task {
    public:
    int id_;
    int version_;
    void updateVersion() {
        this->version_++;
    }

        //constructors
        Task();
        Task(std::string);
        Task(const Task&);
        Task(Task&&);
        //destructors
        ~Task();
        //operators
        friend bool operator==(const Task& left, const Task& right);

        Task& operator=(const Task&);
        Task& operator=(Task&&);
        //getters
        static std::size_t getNumberOfTasks();
        //setters
        void setIsCompleted(const bool);
        void setDescription(const std::string);
        void setAllFields(const std::string,
                          const bool);
        //clearing
        void clearDescription();
        //funcs
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        bool isCompleted_;
        std::string description_;

    private:
        static std::size_t numberOfTasks;
};

std::size_t Task::numberOfTasks = 0;

bool operator==(const Task& left, const Task& right) {
    return (left.description_ == right.description_) &&
           (left.isCompleted_ == right.isCompleted_) &&
           (left.version_ == right.version_);
}

Task::Task() {
    this->isCompleted_ = false;
    description_ = "New Task";
    numberOfTasks++;
}

Task::Task(std::string description) {
    isCompleted_ = false;
    description_ = std::move(description);
    numberOfTasks++;
}


Task::Task(const Task& right) {
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_ = right.version_;
    numberOfTasks++;
}

Task::Task(Task&& right) {
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_ = right.version_;

    right.clearDescription();
}
        //destructors
Task::~Task() {
    numberOfTasks--;
}

Task& Task::operator=(const Task& right) {
    if (this == &right) {
        return *this;
    }
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_ = right.version_;

    return *this;
}

Task& Task::operator=(Task&& right) {
    if (this == &right) {
	    return *this;
    }
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_ = right.version_;

    right.clearDescription();

    return *this;
}

        //setters
void Task::setIsCompleted(const bool isCompleted) {
    isCompleted_ = std::move(isCompleted);
    this->updateVersion();
//    this->base_->update(*this);
}

void Task::setDescription(const std::string description) {
    description_ = std::move(description);
//    this->base_->update(*this);
    this->updateVersion();
}

void Task::setAllFields(const std::string description = "New Task",
                  const bool isCompleted = false) {
    isCompleted_ = std::move(isCompleted);
    description_ = std::move(description);
//    this->base_->update(*this);
    this->updateVersion();
}

        //clearing
void Task::clearDescription() {
    description_.clear();
}
        //funcs
void Task::show() {
    if (isCompleted_) {
        std::cout << "Completed" << std::endl;
    } else {
        std::cout << "Uncompleted" << std::endl;
    }
    std::cout << description_ << std::endl;
}

void Task::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Description: ";
    std::cin >> input;
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }


    std::cout << "Completed? [Y / N]: ";
    std::cin >> input;
    if (!input.empty()) {

        if ((input.find("Y") != std::string::npos) || (input.find("y") != std::string::npos)) {
            this->isCompleted_ = true;
        } else {
            this->isCompleted_ = false;
        }
        input.clear();

    }

    std::cout << std::endl;

//    base_->update(*this);
}

std::string Task::concatenate() {
    return std::to_string(id_)    +SEPARATOR+
           std::to_string(version_)     +SEPARATOR+
           std::to_string(isCompleted_) +SEPARATOR+
           description_;
}

void Task::deconcatenate(const std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;

    for (std::size_t i = 0; i != msg.size(); ++i) {
        if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
                id_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 1) {
                counter++;
                version_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 2) {
                counter++;
                isCompleted_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            }
        }
    }
    description_ = msg.substr(posBegin);
}

std::size_t Task::getNumberOfTasks() {
    return Task::numberOfTasks;
}

class Note {
    public:
    int id_;
    int version_;
    void updateVersion() {
        this->version_++;
    }
        //constructors
        Note();
        Note(std::string,
             std::string,
             std::string);
        Note(const Note&);
        Note(Note&&);
        //destructors
        ~Note();
        //operators
        friend bool operator==(const Note& left, const Note& right);

        Note& operator=(const Note&);
        Note& operator=(Note&&);
        //getters
        static std::size_t getNumberOfNotes();

        //setters
        void setLabel(std::string);
        void setName(std::string);
        void setDescription(std::string);
        void setAllFields(std::string,
                          std::string,
                          std::string);
        //clearing
        void clearName();
        void clearDescription();
        void clearLabel();
        //funcs
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        std::string label_;
        std::string name_;
        std::string description_;

    private:
        static std::size_t numberOfNotes;
};

std::size_t Note::numberOfNotes = 0;


bool operator==(const Note& left, const Note& right) {
    return (left.label_ == right.label_) &&
           (left.name_ == right.name_) &&
           (left.description_ == right.description_) &&
           (left.version_ == right.version_);
}

Note::Note() {
    label_ = "Buffer";
    name_ = "New Task";
    description_ = "New Task";

    numberOfNotes++;

}

Note::Note(std::string name,
    std::string description = "New Note",
    std::string label = "Buffer") {
    label_ = std::move(label);
    name_ = std::move(name);
    description_ = std::move(description);

    numberOfNotes++;
}


Note::Note(const Note& right) {
    label_ = right.label_;
    name_ = right.name_;
    description_ = right.description_;
    version_ = right.version_;
}

Note::Note(Note&& right) {
    label_ = right.label_;
    name_ = right.name_;
    description_ = right.description_;
    version_ = right.version_;


    right.clearLabel();
    right.clearName();
    right.clearDescription();
}
        //destructors
Note::~Note() {
    numberOfNotes--;
}
        //operators
Note& Note::operator=(const Note& other) {
    if (this == &other) {
        return *this;
    }

    label_ = other.label_;
    name_ = other.name_;
    description_ = other.description_;
    version_ = other.version_;

    return *this;
}

Note& Note::operator=(Note&& right) {
    if (this == &right) {
        return *this;
    }
    label_ = right.label_;
    name_ = right.name_;
    description_ = right.description_;
    version_ = right.version_;

    right.clearLabel();
    right.clearName();
    right.clearDescription();

    return *this;
}
        //getters

std::size_t Note::getNumberOfNotes() {
    return Note::numberOfNotes;
}
        //setters
void Note::setLabel(std::string label) {
    this->label_ = std::move(label);
    this->updateVersion();
//    base_->update(*this);
}

void Note::setName(std::string name) {
    this->name_ = std::move(name);
    this->updateVersion();
//    base_->update(*this);
}

void Note::setDescription(std::string description) {
    this->description_ = std::move(description);
    this->updateVersion();
//    base_->update(*this);
}

void Note::setAllFields(std::string name,
                  std::string description = "New Note",
                  std::string label = "Buffer") {
    this->name_ = std::move(name);
    this->description_ = std::move(description);
    this->label_ = std::move(label);
    this->updateVersion();
//    base_->update(*this);
}
        //clearing
void Note::clearName() {
    this->name_.clear();
}

void Note::clearDescription() {
    this->description_.clear();
}

void Note::clearLabel() {
    this->label_.clear();
}
        //funcs
void Note::show() {
    std::cout << "#" << label_ << std::endl;
    std::cout << name_ << std::endl;
    std::cout << description_ << std::endl;
}

void Note::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Label: ";
    std::cin >> input;
    if (!input.empty()) {
        this->label_ = input;
        input.clear();
    }

    std::cout << "Name: ";
    std::cin >> input;
    if (!input.empty()) {
        this->name_ = input;
        input.clear();
    }

    std::cout << "Description: ";
    std::cin >> input;
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }

    std::cout << std::endl;

    this->updateVersion();
//    base_->update(*this);
}


std::string Note::concatenate() {
    return label_                    +SEPARATOR+
           name_                     +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_) +SEPARATOR+
           description_;
}

void Note::deconcatenate(const std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;
    for (std::size_t i = 0; i != msg.size(); ++i) {
    if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
               	label_ = msg.substr(posBegin, i-1);
                posBegin = i+SEPARATOR.size();
            } else if (counter == 1) {
                counter++;
                name_ = msg.substr(posBegin, i-1);
                posBegin = i+SEPARATOR.size();
            } else if (counter == 2) {
                counter++;
                version_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 3) {
                counter++;
                id_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            }
        }
    }
    description_ = msg.substr(posBegin);
}

class Day {
    public:
    int id_;
    int version_;
    void updateVersion() {
        this->version_++;
    }

        Day();
        Day(std::string);
        Day(const Day&);
        Day(Day&&);
        Day& operator=(const Day&);
        Day& operator=(Day&&);

        ~Day() = default;

        friend bool operator==(const Day& left, const Day& right);

        void setDate(std::string);

        void addDeal(Deal);
        void addImportant(Important);

        //todo -------------
        void removeDeal(int);
        void editDeal(int);

        void removeImportant(int);
        void editImportant(int);
        //------------------
        //funcs
        void showDeals();
        void showImportants();
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        std::string date_;
        std::vector<Deal> deals_;
        std::vector<Important> importants_;
};

bool operator==(const Day& left, const Day& right) {
    return (left.date_ == right.date_)   &&
           (left.deals_ == right.deals_) &&
           (left.importants_ == right.importants_) &&
           (left.version_ == right.version_);
}

Day::Day()
{
	date_ = "01 January 1970";
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

Day::Day(std::string date) {
    date_ = std::move(date);
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

Day::Day(const Day& other) {
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version_;
}
Day::Day(Day&& other) {
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version_;
}
Day& Day::operator=(const Day& other) {
    if (this == &other) {
        return *this;
    }
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version_;
    return *this;
}
Day& Day::operator=(Day&& other) {
    if (this == &other) {
        return *this;
    }
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version_;
    return *this;

}


void Day::setDate(std::string date) {
    this->date_ = std::move(date);
    this->updateVersion();
//    this->base_->update(*this);

}

void Day::addDeal(Deal deal) {
    this->deals_.push_back(deal);
    (this->deals_.end()-1)->setDate(this->date_);
}

void Day::addImportant(Important important) {
    this->importants_.push_back(important);
}

//todo -------------
void Day::removeDeal(int pos) {
    pos--;
    auto it = this->deals_.begin() + pos;
//    this->base_->remove<Deal>(it->id_);
    this->deals_.erase(it);
}

void Day::editDeal(int pos) {
    pos--;
    auto it = this->deals_.begin() + pos;
    std::cout << "Editing deal..." << std::endl;
    std::string tmp;
    std::cout << "Please, enter time in such format HH:MM-HH:MM" << std::endl;
    std::cin >> tmp;
    if (!tmp.empty()) {
        it->setTime(tmp.substr(0, 1)+tmp.substr(3, 4), tmp.substr(6, 7)+tmp.substr(9, 10));
    }
    std::cout << "Please, enter label" << std::endl;
    std::cin >> tmp;
    if (!tmp.empty()) {
        it->setLabel(tmp);
    }
    std::cout << "Please, enter priority" << std::endl;
    std::cin >> tmp;
    if (!tmp.empty()) {
        it->setPriority(tmp);
    }
    std::cout << "Please, enter name" << std::endl;
    std::cin >> tmp;
    if (!tmp.empty()) {
        it->setName(tmp);
    }
    std::cout << "Please, enter description" << std::endl;
    std::cin >> tmp;
    if (!tmp.empty()) {
        it->setDescription(tmp);
    }
    it->updateVersion();
//    this->base_->update(*it);
}

void Day::removeImportant(int pos) {
	pos--;
    auto it = this->importants_.begin() + pos;
//    this->base_->remove<Important>(it->id_);
    this->importants_.erase(it);
}

void Day::editImportant(int pos) {
    pos--;
    auto it = this->importants_.begin() + pos;
    std::cout << "Editing important..." << std::endl;
    std::cout << "Please, enter new important" << std::endl;
    std::string tmp;
    std::cin >> tmp;
    it->important_ = tmp;
    it->updateVersion();
//    this->base_->update(*it);
}
//------------------
//funcs
void Day::showDeals() {
    for (auto it = deals_.begin(); it != deals_.end(); ++it) {
        it->show();
    }
}

void Day::showImportants() {
    int i = 1;
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        std::string tmp = it->important_;
        std::cout << i << ". " << tmp << std::endl;
        i++;
    }
}

void Day::show() {
    std::cout << date_ << std::endl;
    this->showDeals();
    this->showImportants();
}

void Day::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Date: ";
    std::cin >> input;
    if (!input.empty()) {
        this->date_ = input;
        input.clear();
    }


    std::cout << "Deals: ";
    for (auto it = deals_.begin(); it != deals_.end(); ++it) {
        it->edit();
    }

    std::cout << "Importants: ";
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        std::cin >> input;
        if (!input.empty()) {
            it->important_ = input;
            input.clear();
        }
    }

    std::cout << std::endl;

    this->updateVersion();
//    this->base_->update(*this);
}

std::string Day::concatenate() {
    std::string tmp;
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp += it->important_;
    }
    return (date_                 +SEPARATOR+
        std::to_string(id_) +SEPARATOR+
        tmp);
}

void Day::deconcatenate(const std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;
    std::size_t numOfImportant = 0;

    for (std::size_t i = 0; i != msg.size(); ++i) {
        if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
                date_ = msg.substr(posBegin, i-1);
                posBegin = i+SEPARATOR.size();
            } else if (counter == 1) {
                counter++;
                id_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter > 1) {
                addImportant(std::string(std::to_string(numOfImportant)+
                             msg.substr(posBegin, i-1)));
                posBegin = i+SEPARATOR.size();
                numOfImportant++;
            }
        }
    }
}

class User {
    friend class Session;
    public:
        User() = default;

        User(std::string, std::string);

        ~User() = default;

        bool isLoggedIn() const;
        std::string login_;
        std::string hashedPass_;
        int id_;
        bool isLoggedIn_;
    private:
        int key_;

        void key_gen();
        std::string doCryptoMessage(std::string);
};

User::User(std::string login, std::string hashedPass) {
    this->login_ = login;
    this->hashedPass_ = hashedPass;
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

inline auto initAccountsDb() {
    using namespace sqlite_orm;
    return make_storage("accounts.sqlite",
                                make_table("Accounts",
                                    make_column("id",
                                        &User::id_,
                                        autoincrement(),
                                        primary_key()),
                                    make_column("login",
                                        &User::login_),
                                    make_column("hashed_pass",
                                        &User::hashedPass_ )));
}

inline auto initLocalDb(const std::string &path) {
    using namespace sqlite_orm;
    return make_storage(path,
                                make_table("Days",

                                    make_column("id",
                                        &Day::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Day::version_),

                                    make_column("Date",
                                        &Day::date_)),

                                make_table("Importants",

                                    make_column("id",
                                        &Important::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Important::version_),

                                    make_column("HashedPass",
                                        &Important::important_ )),

                                make_table("Deals",

                                    make_column("id",
                                        &Deal::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Deal::version_),

                                    make_column("Name",
                                        &Deal::name_),

                                    make_column("Description",
                                        &Deal::description_),

                                    make_column("Label",
                                        &Deal::label_),

                                    make_column("Priority",
                                        &Deal::priority_),

                                    make_column("date",
                                        &Deal::date_)),

                                make_table("Tasks",

                                    make_column("id",
                                        &Task::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Task::version_),

                                    make_column("IsCompleted",
                                        &Task::isCompleted_),

                                    make_column("Description",
                                        &Task::description_)),

                                make_table("Notes",

                                    make_column("id",
                                        &Note::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Note::version_),

                                    make_column("Label",
                                        &Note::label_),

                                    make_column("Name",
                                        &Note::name_),

                                    make_column("Description",
                                        &Note::description_))
    );
}

using Accounts = decltype(initAccountsDb());
using Storage = decltype(initLocalDb(""));

//--------------------
//--------------------
using namespace sqlite_orm;
class Session {
public:
        Session(std::string, std::string);
        ~Session() = default;
        Session() = default;
        Session(const Session&) = default;
        Session(Session&&) = default;
        Session& operator=(const Session&) = default;
        Session& operator=(Session&&) = default;

        User user;
        Accounts accountsDb = initAccountsDb();
        std::shared_ptr<Storage> localDb = nullptr;

        std::vector<Task> tasks_;
        std::vector<Note> notes_;
        std::vector<Day> days_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator
        > joinedObject_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator
        > copyableObject_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator
        > moveableObject_;

        void addingNewUser();

        void logIn();
        void logOut();

        void addTask(Task);
        void addNote(Note);
        void addDay(Day);

        void showJoined();
        void showHelp();

        void creatingTask();
        void creatingNote();
        void creatingDay();
        void creatingDeal();
        void creatingImportant();

        void getDataFromLocalBase();

        void setJoined(std::vector<Day>::iterator);
        void setJoined(std::vector<Deal>::iterator);
        void setJoined(std::vector<Task>::iterator);
        void setJoined(std::vector<Note>::iterator);

        void incrementJoined();
        void decrementJoined();

        void setMovable(std::vector<Day>::iterator&);
        void setMovable(std::vector<Deal>::iterator&);
        void setMovable(std::vector<Task>::iterator&);
        void setMovable(std::vector<Note>::iterator&);

        void setCopyable(std::vector<Day>::iterator&);
        void setCopyable(std::vector<Deal>::iterator&);
        void setCopyable(std::vector<Task>::iterator&);
        void setCopyable(std::vector<Note>::iterator&);

        void setJoinedLabel(const std::string&);
        void setJoinedName(const std::string&);
        void setJoinedDescription(const std::string&);
        void setJoinedPriority(const std::string&);

        void setJoinedTime(const std::string, const std::string);
        void setJoinedComplited(const bool&);
        void setJoinedDate(const std::string&);

        void eraseDealFromJoined(int&);
        void eraseImportantFromJoined(int&);

        void eraseJoinedTask();
        void eraseJoinedNote();
        void eraseJoinedDay();

    private: //visitors

struct JoinedShower {
    void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
};

struct JoinedLabelSetter {
	JoinedLabelSetter(std::string);

    std::string msg_;

    void operator()(std::vector<Deal>::iterator&);
    void operator()(std::vector<Note>::iterator&);
    //not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
    void operator()(std::vector<Task>::iterator& it){};
};

struct JoinedNameSetter {
	JoinedNameSetter(std::string);

    std::string msg_;

	void operator()(std::vector<Deal>::iterator&);
    void operator()(std::vector<Note>::iterator&);
    //not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
    void operator()(std::vector<Task>::iterator& it){};
};

struct JoinedDescriptionSetter {
	JoinedDescriptionSetter(std::string);

    std::string msg_;

	void operator()(std::vector<Deal>::iterator&);
    void operator()(std::vector<Task>::iterator&);
    void operator()(std::vector<Note>::iterator&);
    //not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
};

struct JoinedPrioritySetter {
	JoinedPrioritySetter(std::string);

    std::string msg_;

	void operator()(std::vector<Deal>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
    void operator()(std::vector<Task>::iterator& it){};
    void operator()(std::vector<Note>::iterator& it){};
};

struct JoinedTimeSetter {
	JoinedTimeSetter(std::string, std::string);

    std::string begins;
    std::string ends;

	void operator()(std::vector<Deal>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
    void operator()(std::vector<Task>::iterator& it){};
    void operator()(std::vector<Note>::iterator& it){};
};

struct JoinedComplitedSetter {
	JoinedComplitedSetter(bool);

    bool msg_;
	void operator()(std::vector<Task>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Day>::iterator& it){};
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Note>::iterator& it){};
};

struct JoinedDateSetter {
	JoinedDateSetter(std::string);

    std::string msg_;

	void operator()(std::vector<Day>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Task>::iterator& it){};
    void operator()(std::vector<Note>::iterator& it){};
};

struct CopyablePaster {
    CopyablePaster(Session&);

    Session* session;

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
};

struct JoinedIncrementAllower {
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
};

struct JoinedDecrementAllower {
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
};

struct MovableSetter {
	MovableSetter(Session&);

	Session* session;

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
};

struct CopyableSetter {
	CopyableSetter(Session&);

	Session* session;

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
};
};
Session::CopyableSetter::CopyableSetter(Session& sess) {
	this->session = &sess;
}
void Session::CopyableSetter::operator()(std::vector<Deal>::iterator& it) {
	this->session->copyableObject_ = it;
}
void Session::CopyableSetter::operator()(std::vector<Day>::iterator& it) {
	this->session->copyableObject_ = it;
}
void Session::CopyableSetter::operator()(std::vector<Task>::iterator& it) {
	this->session->copyableObject_ = it;
}
void Session::CopyableSetter::operator()(std::vector<Note>::iterator& it) {
	this->session->copyableObject_ = it;
}

Session::MovableSetter::MovableSetter(Session& sess) {
	this->session = &sess;
}
void Session::MovableSetter::operator()(std::vector<Deal>::iterator& it) {
	this->session->moveableObject_ = it;
}
void Session::MovableSetter::operator()(std::vector<Day>::iterator& it) {
	this->session->moveableObject_ = it;
}
void Session::MovableSetter::operator()(std::vector<Task>::iterator& it) {
	this->session->moveableObject_ = it;
}
void Session::MovableSetter::operator()(std::vector<Note>::iterator& it) {
	this->session->moveableObject_ = it;
}

void Session::JoinedShower::operator()(std::vector<Deal>::iterator& it) {
    it->show();
}
void Session::JoinedShower::operator()(std::vector<Day>::iterator& it) {
    it->show();
}
void Session::JoinedShower::operator()(std::vector<Task>::iterator& it) {
    it->show();
}
void Session::JoinedShower::operator()(std::vector<Note>::iterator& it) {
    it->show();
}

Session::JoinedLabelSetter::JoinedLabelSetter(std::string msg) {
    this->msg_ = std::move(msg);
}
void Session::JoinedLabelSetter::operator()(std::vector<Deal>::iterator& it) {
    it->setLabel(msg_);
//    base->update(*it);
}
void Session::JoinedLabelSetter::operator()(std::vector<Note>::iterator& it) {
    it->setLabel(msg_);
//    base->update(*it);
}

Session::JoinedNameSetter::JoinedNameSetter(std::string msg) {
    this->msg_ = std::move(msg);
}
void Session::JoinedNameSetter::operator()(std::vector<Deal>::iterator& it) {
    it->setName(msg_);
//    base->update(*it);
}
void Session::JoinedNameSetter::operator()(std::vector<Note>::iterator& it) {
    it->setName(msg_);
//    base->update(*it);
}

Session::JoinedDescriptionSetter::JoinedDescriptionSetter(std::string msg) {
    this->msg_ = std::move(msg);
}
void Session::JoinedDescriptionSetter::operator()(std::vector<Deal>::iterator& it) {
    it->setDescription(msg_);
//    base->update(*it);
}
void Session::JoinedDescriptionSetter::operator()(std::vector<Task>::iterator& it) {
    it->setDescription(msg_);
//    base->update(*it);
}
void Session::JoinedDescriptionSetter::operator()(std::vector<Note>::iterator& it) {
    it->setDescription(msg_);
//    base->update(*it);
}

Session::JoinedPrioritySetter::JoinedPrioritySetter(std::string msg) {
    this->msg_ = std::move(msg);
}
void Session::JoinedPrioritySetter::operator()(std::vector<Deal>::iterator& it) {
   	it->setPriority(msg_);
//    base->update(*it);
}

Session::JoinedTimeSetter::JoinedTimeSetter(std::string begins, std::string ends) {
    this->begins = std::move(begins);
    this->ends = std::move(ends);
}
void Session::JoinedTimeSetter::operator()(std::vector<Deal>::iterator& it) {
    it->setTime(begins, ends);
//    base->update(*it);
}

Session::JoinedComplitedSetter::JoinedComplitedSetter(bool msg) {
    this->msg_ = std::move(msg);
}
void Session::JoinedComplitedSetter::operator()(std::vector<Task>::iterator& it) {
   	it->setIsCompleted(msg_);
//    base->update(*it);
}

Session::JoinedDateSetter::JoinedDateSetter(std::string msg) {
	this->msg_ = std::move(msg);
}
void Session::JoinedDateSetter::operator()(std::vector<Day>::iterator& it) {
   	it->setDate(msg_);
 //   base->update(*it);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Session::CopyablePaster::CopyablePaster(Session& sess) {
    this->session = &sess;
}
void Session::CopyablePaster::operator()(std::vector<Day>::iterator& copyable) {
    auto joined = std::get<std::vector<Day>::iterator>(this->session->joinedObject_);

    this->session->days_.insert((joined + 1), *copyable);
}
void Session::CopyablePaster::operator()(std::vector<Task>::iterator& copyable) {
    auto joined = std::get<std::vector<Task>::iterator>(this->session->joinedObject_);

    this->session->tasks_.insert((joined + 1), *copyable);
}
void Session::CopyablePaster::operator()(std::vector<Note>::iterator& copyable) {
    auto joined = std::get<std::vector<Note>::iterator>(this->session->joinedObject_);

    this->session->notes_.insert((joined + 1), *copyable);
}

void Session::JoinedDecrementAllower::operator()(std::vector<Day>::iterator& it) {
    it--;
}
void Session::JoinedDecrementAllower::operator()(std::vector<Task>::iterator& it) {
    it--;
}
void Session::JoinedDecrementAllower::operator()(std::vector<Note>::iterator& it) {
    it--;
}

void Session::JoinedIncrementAllower::operator()(std::vector<Day>::iterator& it) {
    it++;
}
void Session::JoinedIncrementAllower::operator()(std::vector<Task>::iterator& it) {
    it++;
}
void Session::JoinedIncrementAllower::operator()(std::vector<Note>::iterator& it) {
    it++;
}

//private

Session::Session(std::string name, std::string hashedpass)
{
    this->user.login_ = name;
    this->user.hashedPass_ = hashedpass;

    this->localDb = std::make_shared<Storage>(initLocalDb(std::string(name + ".sqlite")));

	tasks_.reserve(100);
    notes_.reserve(1000);
    days_.reserve(3000);
}

//public
void Session::addingNewUser() {
    std::string login;
    std::string password;
    std::cout << "Please, enter new login" << std::endl;
    std::cin >> login;
    try {
        auto user = accountsDb.get_all<User>(where(is_equal(&User::login_, login)));
    }
    catch(...) {
        std::cout << "Please, enter new password" << std::endl;
        std::cin >> password;

        this->user.login_ = login;
        this->user.hashedPass_ = md5(password);

        auto insertedId = accountsDb.insert(this->user);
        this->user.id_ = insertedId;

        std::cout << "New account has been created" << std::endl;
        std::cout << "Now you can log in with entered login and password" << std:: endl;
    }
        std::cout << "Sorry, this login is already exists. Please, try again." << std::endl;
}
//public

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

    try {
        auto ExistingUser = accountsDb.get_all<User>(where(is_equal(&User::login_, login) &&
                                                    is_equal(&User::hashedPass_, hashedPassword)));
        this->user.login_ = login;
		this->user.hashedPass_ = hashedPassword;
        std::cout << "You've succesfully logged in" << std::endl;
        this->user.isLoggedIn_ = true;

    } catch(...) {
        std::cout << "Wrong login or password" << std::endl;
        std::cout << "Please, try again" << std::endl;
    }
}
void Session::logOut() {
    this->user.login_.clear();
    this->user.hashedPass_.clear();
    this->user.isLoggedIn_ = false;
}


void Session::getDataFromLocalBase() {
	try {
        this->tasks_ = localDb->get_all<Task>();
		//this->tasks_ = localDb.get_all<Task>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}


	try {
    	this->notes_ = localDb->get_all<Note>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one note found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}

	try {
    	this->days_ = localDb->get_all<Day>();
	}
	catch (sqlite_orm::orm_error_code) {
      	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << "Unknown exception" << std::endl;
	}

	for (auto it = days_.begin(); it != days_.end(); ++it) {
    	try {
        	it->deals_ = localDb->get_all<Deal>(where(is_equal(&Deal::date_, it->date_)));
    	}
    	catch(sqlite_orm::orm_error_code) {
        	continue;
    	}
    	catch(...) {
        	std::cout << "Unknown exception" << std::endl;
    	}

        try {
            it->importants_ = localDb->get_all<Important>(where(is_equal(&Deal::date_, it->date_)));
        }
        catch(sqlite_orm::orm_error_code) {
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

    Task task(description);
    auto insertedId = localDb->insert(task);
    task.id_= insertedId;
    tasks_.push_back(task);

    std::cout << "New tas has been created :)" << std::endl;
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

    Note note(name, description, label);

    auto insertedId = localDb->insert(note);
    note.id_= insertedId;
    notes_.push_back(note);

    std::cout << "New note has been created :)" << std::endl;
}

void Session::creatingDay() {
    std::string date;
    std::cout << "Please, enter date in format YYYYMMDD" << std::endl;
    std::cin >> date;

    Day day(date);

    auto insertedId = localDb->insert(day);
    day.id_= insertedId;
    days_.push_back(day);

    std::cout << "New day has been created :)" << std::endl;
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
    std::cout << "Please, enter time in format HH:MM-HH:MM" << std::endl;
    std::cin >> time;
    Deal deal(name,
                description,
                label,
                priority,
                time.substr(0, 2)+time.substr(4, 5),
                time.substr(7, 9)+time.substr(11, 12));

    auto insertedId = localDb->insert(deal);
    deal.id_= insertedId;
    std::get<std::vector<Day>::iterator>(joinedObject_)->addDeal(deal);


    std::cout << "New day has been created :)" << std::endl;

}

void Session::creatingImportant() {
    std::string tmp;
    std::cout << "Please, enter important" << std::endl;
    std::cin >> tmp;
    Important important(tmp);

    auto insertedId = localDb->insert(important);
    important.id_ = insertedId;
    std::get<std::vector<Day>::iterator>(joinedObject_)->addImportant(important);

    std::cout << "New important has been created :)" << std::endl;
}

 void Session::addTask(Task task) {
     this->tasks_.push_back(task);
 }

 void Session::addNote(Note note) {
     this->notes_.push_back(note);
 }

 void Session::addDay(Day day) {
     this->days_.push_back(day);
 }

 void Session::showJoined() {
 	std::visit(JoinedShower{}, this->joinedObject_);
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


/*
template<typename T>
void Session::setJoined(std::vector<T>::iterator it) {
	joinedObject_ = it;
}
*/
void Session::setJoined(std::vector<Day>::iterator it) {
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

void Session::incrementJoined() {
	std::visit(Session::JoinedIncrementAllower{}, this->joinedObject_);
}

void Session::decrementJoined() {
	std::visit(Session::JoinedDecrementAllower{}, this->joinedObject_);
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
void Session::setMovable(std::vector<Day>::iterator& it) {
    std::visit(MovableSetter{*this}, this->joinedObject_);
}

void Session::setCopyable(std::vector<Day>::iterator& it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Deal>::iterator& it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Task>::iterator& it) {
    copyableObject_ = it;
}
void Session::setCopyable(std::vector<Note>::iterator& it) {
    copyableObject_ = it;
}

//refactoring needs
//need visit in runtime!!!
void Session::setJoinedLabel(const std::string& msg) {
	std::visit(JoinedLabelSetter{msg}, joinedObject_);
}
void Session::setJoinedName(const std::string& msg) {
	std::visit(JoinedNameSetter{msg}, joinedObject_);
}
void Session::setJoinedDescription(const std::string& msg) {
	std::visit(JoinedDescriptionSetter{msg}, joinedObject_);
}
void Session::setJoinedPriority(const std::string& msg) {
	std::visit(JoinedPrioritySetter{msg}, joinedObject_);
}
void Session::setJoinedTime(const std::string begins, const std::string ends) {
	std::visit(JoinedTimeSetter{begins, ends}, joinedObject_);
}
void Session::setJoinedComplited(const bool& complited) {
    std::visit(JoinedComplitedSetter{complited}, joinedObject_);
}
void Session::setJoinedDate(const std::string& msg) {
	std::visit(JoinedDateSetter{msg}, joinedObject_);
}

void Session::eraseDealFromJoined(int& pos) {
    //this->localDb->remove<Deal>(joinedObject_->deals_[pos-1]);
    (std::get<std::vector<Day>::iterator>(joinedObject_))->removeDeal(pos);
}
void Session::eraseImportantFromJoined(int& pos) {
//    this->localDb->remove<Impportant>(joinedObject_->importants_[pos-1]);
    (std::get<std::vector<Day>::iterator>(joinedObject_))->removeImportant(pos);
}

void Session::eraseJoinedTask() {
//    this->localDb ->remove<Task>(joinedObject_->id_);
    tasks_.erase(std::get<std::vector<Task>::iterator>(joinedObject_));
}
void Session::eraseJoinedNote() {
//    this->localDb ->remove<Note>(joinedObject_->id_);
    notes_.erase(std::get<std::vector<Note>::iterator>(joinedObject_));
}
void Session::eraseJoinedDay() {
//    this->localDb ->remove<Day>(joinedObject_->id_);
    days_.erase(std::get<std::vector<Day>::iterator>(joinedObject_));
}
//--------------------



int main()
{
    std::cout << "Hello world!" << std::endl;
    return 0;
}
