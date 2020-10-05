#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <variant>
#include <cstdlib>

#include "include/sqlite_orm.h"
#include "include/MD5.h"

using namespace sqlite_orm;

const std::string SEPARATOR(1, '`');

std::vector<std::string> split(const std::string& input, char separator) {

    std::vector<std::string> args;

    std::istringstream input_ss {input};

    for (std::string arg; std::getline(input_ss, arg, separator); ) {
        args.push_back(arg);
    }

    return args;
}

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

        std::string begin_;
        std::string end_;

};

bool operator==(const Deal& left, const Deal& right) {
    return (left.name_          == right.name_)        &&
           (left.description_   == right.description_) &&
           (left.label_         == right.label_)       &&
           (left.priority_      == right.priority_)    &&
           (left.begin_         == right.begin_)       &&
           (left.end_           == right.end_)         &&
           (left.version_       == right.version_);
}

Deal::Deal() {
    description_ = "New Deal";
    name_        = "New Deal";
    label_       = "My Deals";
    priority_    = "A";
    begin_       = "0000";
    end_         = "0100";
}

Deal::Deal(std::string name,
     std::string description = "No description",
     std::string label       = "My Deals",
     std::string priority    = "A",
     std::string begins      = "0000",
     std::string ends        = "0000") {
    name_        = name;
    description_ = description;
    label_       = label;
    priority_    = priority;
    begin_       = begins;
    end_         = ends;
}

Deal::Deal(const Deal& other) {
    name_        = other.name_;
    description_ = other.description_;
    label_       = other.label_;
    priority_    = other.priority_;
    begin_       = other.begin_;
    end_         = other.end_;
    version_     = other.version_;
}

Deal::Deal(Deal&& other) {
    name_        = other.name_;
    description_ = other.description_;
    label_       = other.label_;
    priority_    = other.priority_;
    begin_       = other.begin_;
    end_         = other.end_;
    version_     = other.version_;

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
    name_        = other.name_;
    description_ = other.description_;
    label_       = other.label_;
    priority_    = other.priority_;
    begin_       = other.begin_;
    end_         = other.end_;
    version_     = other.version_;

    return *this;
}

Deal& Deal::operator=(Deal&& other) {
    if (this == &other) {
        return *this;
    }
    name_        = other.name_;
    description_ = other.description_;
    label_       = other.label_;
    priority_    = other.priority_;
    begin_       = other.begin_;
    end_         = other.end_;
    version_     = other.version_;

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
    begin_.clear();
    end_.clear();
}
//getters

//setters

void Deal::setName(std::string name) {
    name_ = name;
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setDescription(std::string description) {
    description_ = description;
    updateVersion();
    //base_->update(*this);
}

void Deal::setLabel(std::string label) {
    label_ = label;
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setPriority(std::string priority) {
    priority_ = priority;
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setTime(std::string begins, std::string ends) {
    begin_ = begins;
    end_ = ends;
    this->updateVersion();
    //base_->update(*this);
}

void Deal::setDate(std::string date) {
    this->date_ = date;
    this->updateVersion();
    //base_->update(*this);
}

void Deal::show() {
    //todo formatting time
    std::cout << std::setw(13)  << "Time: ";
    std::cout << begin_.substr(0, 2) << ":" << begin_.substr(2, 2)
              << "-"
              << end_.substr(0, 2) << ":" << end_.substr(2, 2)
              << std::endl;

    std::cout << std::setw(13)  << "Label: ";
    std::cout << "#" << label_ << std::endl;

    std::cout << std::setw(13)  << "Priority: ";
    std::cout << priority_ << std::endl;

    std::cout << std::setw(13)  << "Name: ";
    std::cout << name_ << std::endl;

    std::cout << std::setw(13)  << "Description: ";
    std::cout << description_ << std::endl;

    std::cout << std::endl;

}

void Deal::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Name: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->name_ = input;
        input.clear();
    }

    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }

    std::cout << std::setw(13) <<  "Label: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->label_ = input;
        input.clear();
    }

    std::cout << std::setw(13) <<  "Priority: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->priority_ = input;
        input.clear();
    }

    std::cout << std::setw(13) <<  "Begins at ";
    std::getline(std::cin, input, '\n');
    //need to refactor
    if (!input.empty() && input.size() == 4) {
        this->begin_ = input;
        input.clear();
    }

    std::cout << std::setw(13) <<  "Ends at ";
    std::getline(std::cin, input, '\n');
    if (!input.empty() && input.size() == 4) {
        this->end_ = input;
        input.clear();
    }

    std::cout << std::endl;

    std::cout << std::endl;
    this->updateVersion();
//    base_->update(*this);
}

std::string Deal::concatenate() {
    return begin_                    +SEPARATOR+
           end_                      +SEPARATOR+
           name_                     +SEPARATOR+
           label_                    +SEPARATOR+
           priority_                 +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_)       +SEPARATOR+
           description_;
}

void Deal::deconcatenate(std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    begin_       = v[0];
    end_         = v[1];
    name_        = v[2];
    label_       = v[3];
    priority_    = v[4];
    version_     = std::stoi(v[5]);
    id_          = std::stoi(v[6]);
    description_ = v[7];
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
           (left.version_     == right.version_);
}

Task::Task() {
    this->isCompleted_ = false;
    description_ = "New Task";
    numberOfTasks++;
}

Task::Task(std::string description) {
    isCompleted_ = false;
    description_ = description;
    numberOfTasks++;
}


Task::Task(const Task& right) {
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_     = right.version_;
    numberOfTasks++;
}

Task::Task(Task&& right) {
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_     = right.version_;

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
    version_     = right.version_;

    return *this;
}

Task& Task::operator=(Task&& right) {
    if (this == &right) {
	    return *this;
    }
    isCompleted_ = right.isCompleted_;
    description_ = right.description_;
    version_     = right.version_;

    right.clearDescription();

    return *this;
}

        //setters
void Task::setIsCompleted(const bool isCompleted) {
    isCompleted_ = std::isCompleted;
    this->updateVersion();
//    this->base_->update(*this);
}

void Task::setDescription(const std::string description) {
    description_ = description;
//    this->base_->update(*this);
    this->updateVersion();
}

void Task::setAllFields(const std::string description = "New Task",
                  const bool isCompleted = false) {
    isCompleted_ = isCompleted;
    description_ = description;
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
        std::cout << std::setw(13) << "Status: ";
        std::cout << "Completed" << std::endl;
    } else {
        std::cout << std::setw(13) << "Status: ";
        std::cout << "Uncompleted" << std::endl;
    }
    std::cout << std::setw(13) << "Description: ";
    std::cout << description_ << std::endl;

    std::cout << std::endl;
}

void Task::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }


    std::cout << std::setw(13) << "Completed? [Y / N]: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {

        if ((input.find("Y") != std::string::npos) || (input.find("y") != std::string::npos)) {
            this->isCompleted_ = true;
        } else {
            this->isCompleted_ = false;
        }
        input.clear();

    }

    std::cout << std::endl;
    std::cout << std::endl;

//    base_->update(*this);
}

std::string Task::concatenate() {
    return std::to_string(id_)          +SEPARATOR+
           std::to_string(version_)     +SEPARATOR+
           std::to_string(isCompleted_) +SEPARATOR+
           description_;
}

void Task::deconcatenate(const std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    id_          = std::stoi(v[0]);
    version_     = std::stoi(v[1]);
    isCompleted_ = std::stoi(v[2]);
    description_ = v[3];
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
    return (left.label_       == right.label_) &&
           (left.name_        == right.name_) &&
           (left.description_ == right.description_) &&
           (left.version_     == right.version_);
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
    label_       = label;
    name_        = name;
    description_ = description;

    numberOfNotes++;
}


Note::Note(const Note& right) {
    label_       = right.label_;
    name_        = right.name_;
    description_ = right.description_;
    version_     = right.version_;
}

Note::Note(Note&& right) {
    label_       = right.label_;
    name_        = right.name_;
    description_ = right.description_;
    version_     = right.version_;


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

    label_       = other.label_;
    name_        = other.name_;
    description_ = other.description_;
    version_     = other.version_;

    return *this;
}

Note& Note::operator=(Note&& right) {
    if (this == &right) {
        return *this;
    }
    label_       = right.label_;
    name_        = right.name_;
    description_ = right.description_;
    version_     = right.version_;

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
    this->label_ = label;
    this->updateVersion();
//    base_->update(*this);
}

void Note::setName(std::string name) {
    this->name_ = name;
    this->updateVersion();
//    base_->update(*this);
}

void Note::setDescription(std::string description) {
    this->description_ = description;
    this->updateVersion();
//    base_->update(*this);
}

void Note::setAllFields(std::string name,
                  std::string description = "New Note",
                  std::string label = "Buffer") {
    this->name_        = name;
    this->description_ = description;
    this->label_       = label;
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
    std::cout << std::setw(13) << "Label: ";
    std::cout << "#" << label_ << std::endl;

    std::cout << std::setw(13) << "Name: ";
    std::cout << name_ << std::endl;

    std::cout << std::setw(13) << "Description: ";
    std::cout << description_ << std::endl;
}

void Note::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Label: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->label_ = input;
        input.clear();
    }

    std::cout << std::setw(13) << "Name: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->name_ = input;
        input.clear();
    }

    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }

    std::cout << std::endl;
    std::cout << std::endl;

    this->updateVersion();
//    base_->update(*this);
}


std::string Note::concatenate() {
    return label_                    +SEPARATOR+
           name_                     +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_)       +SEPARATOR+
           description_;
}

void Note::deconcatenate(const std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    label_       = v[0];
    name_        = v[1];
    version_     = std::stoi(v[2]);
    id_          = std::stoi(v[3]);
    description_ = v[4];
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
    return (left.date_       == right.date_)   &&
           (left.deals_      == right.deals_) &&
           (left.importants_ == right.importants_) &&
           (left.version_    == right.version_);
}

Day::Day()
{
	date_ = "01 January 1970";
    importants_.emplace_back("Nothing");
    deals_.emplace_back("First of All");
}

Day::Day(std::string date) {
    date_ = date;
    importants_.emplace_back("Nothing");
    deals_.emplace_back("First of All");
}

Day::Day(const Day& other) {
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
}
Day::Day(Day&& other) {
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
}
Day& Day::operator=(const Day& other) {
    if (this == &other) {
        return *this;
    }
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
    return *this;
}
Day& Day::operator=(Day&& other) {
    if (this == &other) {
        return *this;
    }
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
    return *this;

}


void Day::setDate(std::string date) {
    this->date_ = date;
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

    std::string tmp;
    std::cout << std::setw(20) << "Time (HH:MM-HH:MM): " << std::endl;
    std::cout << std::endl;

    std::getline(std::cin, tmp, '\n');
    if (!tmp.empty()) {
        it->setTime(tmp.substr(0, 1)+tmp.substr(3, 4), tmp.substr(6, 7)+tmp.substr(9, 10));
    }
    std::cout << std::setw(20) <<  "Label: " << std::endl;
    std::getline(std::cin, tmp, '\n');
    if (!tmp.empty()) {
        it->setLabel(tmp);
    }
    std::cout << std::setw(20) <<  "Priority: " << std::endl;
    std::getline(std::cin, tmp, '\n');
    if (!tmp.empty()) {
        it->setPriority(tmp);
    }
    std::cout << std::setw(20) << "Name: " << std::endl;
    std::getline(std::cin, tmp, '\n');
    if (!tmp.empty()) {
        it->setName(tmp);
    }
    std::cout << std::setw(20) << "Description: " << std::endl;
    std::getline(std::cin, tmp, '\n');
    if (!tmp.empty()) {
        it->setDescription(tmp);
    }

    std::cout << std::endl;
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
    std::cout << std::endl;

    std::cout << "Please, enter new important: ";
    std::string tmp;
    std::cin >> tmp;
    it->important_ = tmp;
    std::cout << std::endl;

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
    std::cout << std::setw(13) << "Date: ";
    std::cout<< date_ << std::endl;
    std::cout << std::endl;
    this->showDeals();
    this->showImportants();
}

void Day::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Date: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->date_ = input;
        input.clear();
    }


    std::cout << std::setw(13) << "Deals: ";
    for (auto it = deals_.begin(); it != deals_.end(); ++it) {
        it->edit();
    }

    std::cout << std::setw(13) << "Importants: ";
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        std::getline(std::cin, input, '\n');
        if (!input.empty()) {
            it->important_ = input;
            input.clear();
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;

    this->updateVersion();
//    this->base_->update(*this);
}

std::string Day::concatenate() {
    std::string tmp = importants_.begin()->important_;

    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp = SEPARATOR + it->important_;
    }

    return (date_           +SEPARATOR+
        std::to_string(id_) +SEPARATOR+
        tmp);
}

void Day::deconcatenate(const std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    date_ = v[0];
    id_   = std::stoi(v[1]);

    for (int i = 2; i != v.size(); i++) {
        Important important(v[i]);
        this->importants_.push_back(important);
    }
}

class User {
    friend class Session;
    public:
        User();

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

User::User() {
    this->isLoggedIn_ = false;
}

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

                                    make_column("Begin",
                                        &Deal::begin_),

                                    make_column("End",
                                        &Deal::end_),

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

struct CommandChecker;
class Session {
public:
        Session(User*);
        ~Session() = default;
        Session() = default;
        Session(const Session&) = default;
        Session(Session&&) = default;
        Session& operator=(const Session&) = default;
        Session& operator=(Session&&) = default;

        friend CommandChecker;

        User* user;

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

struct JoinedEditor {
    void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
};


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
    CopyablePaster(Session*);

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
	CopyableSetter(Session*);

	Session* session;

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
};
};
Session::CopyableSetter::CopyableSetter(Session* sess) {
	this->session = sess;
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

void Session::JoinedEditor::operator()(std::vector<Day>::iterator& it) {
    it->edit();
}
void Session::JoinedEditor::operator()(std::vector<Deal>::iterator& it) {
    it->edit();
}
void Session::JoinedEditor::operator()(std::vector<Task>::iterator& it) {
    it->edit();
}
void Session::JoinedEditor::operator()(std::vector<Note>::iterator& it) {
    it->edit();
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
Session::CopyablePaster::CopyablePaster(Session* sess) {
    this->session = sess;
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

Session::Session(User* user)
{
    this->user = user;
    std::string databaseName = this->user->login_ + ".sqlite";
    this->localDb = std::make_shared<Storage>(initLocalDb(std::string(databaseName)));
    this->localDb->sync_schema();
    this->getDataFromLocalBase();

	tasks_.reserve(100);
    notes_.reserve(1000);
    days_.reserve(3000);
}

//public

void Session::getDataFromLocalBase() {
	try {
        this->tasks_ = localDb->get_all<Task>();
		//this->tasks_ = localDb.get_all<Task>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one task found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Tasks::New user detected" << std::endl;
	}


	try {
    	this->notes_ = localDb->get_all<Note>();
	}
	catch (sqlite_orm::orm_error_code) {
    	std::cout << "No one note found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Notes::New user detected" << std::endl;
	}

	try {
    	this->days_ = localDb->get_all<Day>();
	}
	catch (sqlite_orm::orm_error_code) {
      	std::cout << "No one day found" << std::endl;
	}
	catch(...) {
    	std::cout << std::setw(24) << "Days::New user detected" << std::endl;
	}

	for (auto it = days_.begin(); it != days_.end(); ++it) {
    	try {
        	it->deals_ = localDb->get_all<Deal>(where(is_equal(&Deal::date_, it->date_)));
    	}
    	catch(sqlite_orm::orm_error_code) {
        	continue;
    	}
    	catch(...) {
        	std::cout << "Deals::New user detected" << std::endl;
    	}

        try {
            it->importants_ = localDb->get_all<Important>(where(is_equal(&Deal::date_, it->date_)));
        }
        catch(sqlite_orm::orm_error_code) {
            continue;
        }
        catch(...) {
            std::cout << "Importants::New user detected" << std::endl;
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

    std::cout << "New day has been created :)" << std::endl;
    std::cout << std::endl;
}

void Session::creatingDeal() {
    std::string name;
    std::string description;
    std::string label;
    std::string priority;
    std::string time;

    std::cout << std::setw(20) << "Name: ";
    std::getline(std::cin, name, '\n');
    std::cout << std::setw(20) << "Description: ";
    std::getline(std::cin, description, '\n');
    std::cout << std::setw(20) << "Label: ";
    std::getline(std::cin, label, '\n');
    std::cout << std::setw(20) << "Priority: ";
    std::getline(std::cin, priority, '\n');
    std::cout << std::setw(20) << "Time (HH:MM-HH:MM): ";
    std::getline(std::cin, time, '\n');
    std::cout << std::endl;

    Deal deal(name,
                description,
                label,
                priority,
                time.substr(0, 2)+time.substr(3, 2),
                time.substr(6, 2)+time.substr(9, 2));

    deal.setDate(std::get<std::vector<Day>::iterator>(joinedObject_)->date_);

    auto insertedId = localDb->insert(deal);
    deal.id_= insertedId;
    std::get<std::vector<Day>::iterator>(joinedObject_)->addDeal(deal);


    std::cout << "New deal has been created :)" << std::endl;
    std::cout << std::endl;

}

void Session::creatingImportant() {
    std::string tmp;
    std::cout << std::setw(13) << "Important: ";
    std::getline(std::cin, tmp, '\n');
    std::cout << std::endl;
    Important important(tmp);

    auto insertedId = localDb->insert(important);
    important.id_ = insertedId;
    std::get<std::vector<Day>::iterator>(joinedObject_)->addImportant(important);

    std::cout << "New important has been created :)" << std::endl;
    std::cout << std::endl;
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

    std::cout << std::endl;

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
 	std::cout << "logout                    -allows to logout from  account"                                   << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Manipulating with server--"                                                                << std::endl;
 	std::cout << "connect                   -allows to connect to server"                                      << std::endl;
 	std::cout << "disconnect                -allows to disconnect from server"                                 << std::endl;
 	std::cout << "sync                      -synchronises local and server databases"                          << std::endl;

 	std::cout << std::endl;

 	std::cout << "--Other--"                                                                                   << std::endl;
 	std::cout << "exit                      -sync bases, disconnect from server and logout"                    << std::endl;

 	std::cout << std::endl;
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

Accounts accountsDb = initAccountsDb();

struct AccessProvider {
    AccessProvider(User*);
    User* user;
    void addingNewUser();
    void logIn();
    void logOut();
    void accessChecker(const std::string&, const std::string&);

};

AccessProvider::AccessProvider(User* user) {
    this->user = user;
}

void AccessProvider::addingNewUser() {
    std::string login;
    std::string password;
    std::cout << "Please, enter new login" << std::endl;
    std::getline(std::cin, login, '\n');
        //throws an exception if such user doesn't exist

        std::vector<User> isUserExists = ::accountsDb.get_all<User>(where(is_equal(&User::login_, login)));

        if (isUserExists.empty()) {
            std::cout << "Please, enter new password" << std::endl;
            std::getline(std::cin, password, '\n');

            this->user->login_ = login;
            this->user->hashedPass_ = md5(password);

            auto insertedId = accountsDb.insert(*(this->user));
            this->user->id_ = insertedId;
            ::accountsDb.update(*user);

            std::cout << "New account has been created" << std::endl;
            std::cout << "Now you can log in with entered login and password" << std:: endl;
            std::cout << std::endl;
        } else {
            std::cout << "Sorry, this login is already exists. Please, try again." << std::endl;
            std::cout << std::endl;
        }
}
//public

void AccessProvider::logIn() {

    std::string login;
    std::string password;
    std::string hashedPassword;

    std::cout << std::setw(13) << "Login: ";
    std::getline(std::cin, login, '\n');
    std::cout << std::endl;

    std::cout << std::setw(13) << "Password: ";
    std::getline(std::cin, password, '\n');
    std::cout << std::endl;

    hashedPassword = md5(password);

    auto ExistingUser = accountsDb.get_all<User>(where(is_equal(&User::login_, login) &&
                                                    is_equal(&User::hashedPass_, hashedPassword)));
    if (!ExistingUser.empty()) {
        this->user->login_ = login;
        this->user->hashedPass_ = hashedPassword;
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
}

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
            std::cout << "---List of supported commands before you log in---"                                          << std::endl;

            std::cout << std::endl;

            std::cout << "add user                  -allows to create new account"                                     << std::endl;
            std::cout << "log in                    -allows to log in in account"                                      << std::endl;
            std::cout << "exit                      -allow to close this app"                                          << std::endl;

            std::cout << std::endl;
        }

        else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;
        }
}

struct CommandChecker {
    CommandChecker(Session*, AccessProvider*);
    Session* thisSession;
    AccessProvider* accessProvider;
    void clearConsole();
    void commandMonitor(const std::string&,
                        const std::string&,
                        const int&);
};

CommandChecker::CommandChecker(Session* session, AccessProvider* accessProvider) {
    this->thisSession = session;
    this->accessProvider = accessProvider;
}

void CommandChecker::clearConsole() {
    for (int i = 0; i != 100; ++i) {
        std::cout << "\n";
    }
}
void CommandChecker::commandMonitor(const std::string& arg1,
                                    const std::string& arg2,
                                    const int& arg3) {

    //method compare returns 0 if string are fully equal
    if (!arg1.compare("next")) {
        std::visit(Session::JoinedIncrementAllower{}, this->thisSession->joinedObject_);
        std::visit(Session::JoinedShower{}, this->thisSession->joinedObject_);
    }
    else if (!arg1.compare("prev")) {
        std::visit(Session::JoinedDecrementAllower{}, this->thisSession->joinedObject_);
        std::visit(Session::JoinedShower{}, this->thisSession->joinedObject_);
    }
    else if (!arg1.compare("join")) {

        if (!arg2.compare("deals")) {
            //need to check
                auto it = std::get<std::vector<Day>::iterator>(thisSession->joinedObject_);
                auto to_set = it->deals_.end() - 1;
                thisSession->setJoined(to_set);
        }

    }
    else if (!arg1.compare("create")) {

        if (!arg2.compare("task")) {

            thisSession->creatingTask();

        } else if (!arg2.compare("note")) {

            thisSession->creatingNote();

        } else if (!arg2.compare("day")) {

            thisSession->creatingDay();

        } else if (!arg2.compare("deal")){

            thisSession->creatingDeal();

        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    }
    else if (!arg1.compare("edit")) {

        std::visit(Session::JoinedEditor{}, thisSession->joinedObject_);

    }
    else if (!arg1.compare("copy")) {

        std::visit(Session::CopyableSetter{thisSession}, thisSession->joinedObject_);
        //or thisSession->copyableObject = thisSession->joinedObject_; ???
    }
    else if (!arg1.compare("paste")) {

        std::visit(Session::CopyablePaster{thisSession}, thisSession->copyableObject_);

    }
    else if (!arg1.compare("remove")) {

        if (!arg2.compare("task")) {

            auto it = std::get<std::vector<Task>::iterator>(thisSession->joinedObject_);

            thisSession->localDb->remove<Task>(it->id_);
            thisSession->tasks_.erase(it);

        } else if (!arg2.compare("note")) {

            auto it = std::get<std::vector<Note>::iterator>(thisSession->joinedObject_);

            thisSession->localDb->remove<Note>(it->id_);
            thisSession->notes_.erase(it);

        } else if (!arg2.compare("day")) {

            auto it = std::get<std::vector<Day>::iterator>(thisSession->joinedObject_);

            thisSession->localDb->remove<Day>(it->id_);
            thisSession->days_.erase(it);

        } else if (!arg2.compare("deal")) {

            auto it = std::get<std::vector<Day>::iterator>(thisSession->joinedObject_);

            if (arg3 <= (it->deals_.size())) {
                thisSession->localDb->remove<Deal>(it->deals_[arg3-1].id_);
                it->removeDeal(arg3);
            } else {
                std::cout << "There is no such deal" << std::endl;
                std::cout << std::endl;
            }

        } else if (!arg2.compare("important")) {

            auto it = std::get<std::vector<Day>::iterator>(thisSession->joinedObject_);

            if (arg3 <= (it->importants_.size())) {
                thisSession->localDb->remove<Important>(it->importants_[arg3-1].id_);
                it->removeImportant(arg3);
            } else {
                std::cout << "There is no suchi mportant" << std::endl;
                std::cout << std::endl;
            }

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }
    else if (!arg1.compare("open")) {

        if (!arg2.compare("tasks")) {
            auto it = thisSession->tasks_.end() - 1;
            thisSession->setJoined(it);

            std::visit(Session::JoinedShower{}, this->thisSession->joinedObject_);

        } else if (!arg2.compare("notes")) {
            auto it = thisSession->notes_.end() - 1;
            thisSession->setJoined(it);

            std::visit(Session::JoinedShower{}, this->thisSession->joinedObject_);

        } else if (!arg2.compare("days")) {

            auto it = thisSession->days_.end() - 1;
            thisSession->setJoined(it);

            std::visit(Session::JoinedShower{}, this->thisSession->joinedObject_);

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }

    else if (!arg1.compare("logout")) {

        this->accessProvider->logOut();

    }
    else if (!arg1.compare("connect")) {

        //thisSession.connectToServer(); //todo

    }
    else if ((!arg1.compare("disconnect"))) {

        //thisSession.disconnectFromServer(); //todo

    }
    else if (!arg1.compare("sync")) {

        //thisSession.syncBases(); //todo

    }
    else if (!arg1.compare("exit")) {

        //thisSession.syncBases(); // todo
        //thisSession.disconnectFromServer(); //todo
        accessProvider->logOut();
        exit(0);

    }
    else if (!arg1.compare("help")) {

        thisSession->showHelp();

    }
    else {
        std::cout << "Wrong command. Please, check 'help'" << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    accountsDb.sync_schema();
    User user;
    AccessProvider accessProvider(&user);

    std::cout << "Welcome to CLICalendar. Please, log in or add new user" << std::endl;
    std::cout << "Write 'help' to get list of commands" << std::endl;
    std::cout << std::endl;

    while(1) {

        while (user.isLoggedIn() == false) {
            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');
            std::cout << std::endl;

            /*if (input.empty()) {
                std::cout << "Empty command" << std::endl;
                continue;
            }*/

            std::vector<std::string> v = split(input, ' ');
            std::cin.clear();
            if ( v.size() == 1 ) {
                accessProvider.accessChecker(v[0], std::string(""));
            }
            else if ( v.size() == 2) {
                accessProvider.accessChecker(v[0], v[1]);
            }
            input.clear();
        }

        Session thisSession(&user);
        thisSession.localDb->sync_schema();

        CommandChecker commandChecker(&thisSession, &accessProvider);

        while(user.isLoggedIn() == true) {
            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');

            /*if (input.empty()) {
                std::cout << "Empty command" << std::endl;
                continue;
            }*/

            std::vector<std::string> v = split(input, ' ');
            std::cin.clear();

            if ( v.size() == 1 ) {
                commandChecker.commandMonitor(v[0], std::string(""), -1);
            }
            else if ( v.size() == 2) {
                commandChecker.commandMonitor(v[0], v[1], -1);
            }
            else if ( v.size() == 3) {
                    int arg3 = -1;
                try {
                    arg3 = std::stoi(v[2]);
                } catch(...) {
                    std::cout << "Third argument must be an integer!" << std::endl;
                    std::cout << "Try again" << std::endl;
                    std::cout << std::endl;
                    continue;
                }
                commandChecker.commandMonitor(v[0], v[1], arg3);
            }
            input.clear();
        }

    }
    return 0;
}
