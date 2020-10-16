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
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <ncurses.h>
#include <exception>
#include <chrono>
#include <thread>
#include <filesystem>

#include "include/sqlite_orm.h"

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
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

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

        //setters
        void setName(std::string);
        void setDescription(std::string);
        void setLabel(std::string);
        void setPriority(std::string);
        void setTime(std::string, std::string);
        void setDate(std::string);


        //user's interface
        void edit();
        void show();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string&);

        //members
        std::string date_;        //need to associating with Day  in databases
        std::string name_;
        std::string description_;
        std::string label_;
        std::string priority_;
        std::string begin_;       //begin deal at
        std::string end_;         //end deal at

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
    this->description_ = "New Deal";
    this->name_        = "New Deal";
    this->label_       = "My Deals";
    this->priority_    = "A";
    this->begin_       = "0000";
    this->end_         = "0100";
    this->id_          = -1;
    this->version_     = 1;
}

Deal::Deal(std::string name,
            std::string description = "No description",
            std::string label       = "My Deals",
            std::string priority    = "A",
            std::string begins      = "0000",
            std::string ends        = "0000") {
    this->name_        = name;
    this->description_ = description;
    this->label_       = label;
    this->priority_    = priority;
    this->begin_       = begins;
    this->end_         = ends;
    this->id_          = -1;
    this->version_     = 1;
}

Deal::Deal(const Deal& other) {
    this->name_        = other.name_;
    this->description_ = other.description_;
    this->label_       = other.label_;
    this->priority_    = other.priority_;
    this->begin_       = other.begin_;
    this->end_         = other.end_;
    this->version_     = other.version_;
    this->id_          = other.id_;
}

Deal::Deal(Deal&& other) {
    this->name_        = other.name_;
    this->description_ = other.description_;
    this->label_       = other.label_;
    this->priority_    = other.priority_;
    this->begin_       = other.begin_;
    this->end_         = other.end_;
    this->version_     = other.version_;
    this->id_          = other.id_;
}
//operators

Deal& Deal::operator=(const Deal& other) {
    if (this == &other) {
        return *this;
    }
    this->name_        = other.name_;
    this->description_ = other.description_;
    this->label_       = other.label_;
    this->priority_    = other.priority_;
    this->begin_       = other.begin_;
    this->end_         = other.end_;
    this->version_     = other.version_;
    this->id_          = other.id_;

    return *this;
}

Deal& Deal::operator=(Deal&& other) {
    if (this == &other) {
        return *this;
    }
    this->name_        = other.name_;
    this->description_ = other.description_;
    this->label_       = other.label_;
    this->priority_    = other.priority_;
    this->begin_       = other.begin_;
    this->end_         = other.end_;
    this->version_     = other.version_;
    this->id_          = other.id_;

    return *this;
}

//setters

void Deal::setName(std::string name) {
    this->name_ = name;
    this->updateVersion();
}

void Deal::setDescription(std::string description) {
    this->description_ = description;
    this->updateVersion();
}

void Deal::setLabel(std::string label) {
    this->label_ = label;
    this->updateVersion();
}

void Deal::setPriority(std::string priority) {
    this->priority_ = priority;
    this->updateVersion();
}

void Deal::setTime(std::string begins, std::string ends) {
    this->begin_ = begins;
    this->end_ = ends;
    this->updateVersion();
}

void Deal::setDate(std::string date) {
    this->date_ = date;
    this->updateVersion();
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

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    this->show();

    std::string input;

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

    std::cout << std::setw(13) <<  "Begins at (HHMM)";
    std::getline(std::cin, input, '\n');

    if (!input.empty()) {
        this->begin_ = input;
        input.clear();
    }

    std::cout << std::setw(13) <<  "Ends at (HHMM)";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->end_ = input;
        input.clear();
    }
    std::cout << std::endl;

    std::cout << std::endl;
    this->updateVersion();
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

class Important {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

        Important();
        Important(std::string);
        Important(const Important&);
        Important(Important&&);

        //operators
        friend bool operator==(const Important& left, const Important& right);
        Important& operator=(const Important&);
        Important& operator=(Important&&);

        //destructor
        ~Important() = default;

        //setters
        void setImportant(std::string);
        void setDate(std::string);

        //user's interface
        void edit();
        void show();

        //members
        std::string important_;
        std::string date_;      //need to associating with Day  in databases
};

bool operator==(const Important& left, const Important& right) {
    return left.important_ == right.important_;
}

Important::Important() {
    this->id_      = -1;
    this->version_ = 1;
}
Important::Important(std::string important) {
    this->important_ = important;
    this->id_        = -1;
    this->version_   = 1;
}
Important::Important(const Important& other) {
	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
}
Important::Important(Important&& other) {
	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
}
Important& Important::operator=(const Important& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;

	return *this;

}
Important& Important::operator=(Important&& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;

	return *this;
}

void Important::show() {
    std::cout << std::setw(13) << important_ << std::endl;
}
void Important::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Important: " << std::endl;
    std::getline(std::cin, input, '\n');
    std::cout << std::endl;
    if (input.size() > 1) {
        this->important_ = input;
        input.clear();
    }

    this->updateVersion();
}

void Important::setImportant(std::string msg) {
	this->important_ = msg;
}
void Important::setDate(std::string date) {
    this->date_ = date;
}

class Task {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

        Task();
        Task(std::string);
        Task(const Task&);
        Task(Task&&);

        //operators
        friend bool operator==(const Task& left, const Task& right);
        Task& operator=(const Task&);
        Task& operator=(Task&&);

        //destructor
        ~Task();

        //getters
        static std::size_t getNumberOfTasks();

        //setters
        void setIsCompleted(const bool);
        void setDescription(const std::string);
        void setAllFields(const std::string,
                          const bool);

        //user's interface
        void edit();
        void show();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(const std::string&);

        //members
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
    this->description_ = "New Task";
    this->id_          = -1;
    this->version_     = 1;
    numberOfTasks++;
}

Task::Task(std::string description) {
    this->isCompleted_ = false;
    this->description_ = description;
    this->id_          = -1;
    this->version_     = 1;
    numberOfTasks++;
}


Task::Task(const Task& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
    numberOfTasks++;
}

Task::Task(Task&& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
}

Task::~Task() {
    numberOfTasks--;
}

Task& Task::operator=(const Task& right) {
    if (this == &right) {
        return *this;
    }

    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

    return *this;
}

Task& Task::operator=(Task&& right) {
    if (this == &right) {
	    return *this;
    }

    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

    return *this;
}

void Task::setIsCompleted(const bool isCompleted) {
    this->isCompleted_ = isCompleted;
    this->updateVersion();
}

void Task::setDescription(const std::string description) {
    this->description_ = description;
    this->updateVersion();
}

void Task::setAllFields(const std::string description = "New Task",
                        const bool isCompleted = false) {

    this->isCompleted_ = isCompleted;
    this->description_ = description;
    this->updateVersion();
}

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

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    this->show();

    std::string input;

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
    this->updateVersion();
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
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

        Note();
        Note(std::string,
             std::string,
             std::string);
        Note(const Note&);
        Note(Note&&);

        //operators
        friend bool operator==(const Note& left, const Note& right);
        Note& operator=(const Note&);
        Note& operator=(Note&&);

        //destructor
        ~Note();

        //getters
        static std::size_t getNumberOfNotes();

        //setters
        void setLabel      (std::string);
        void setName       (std::string);
        void setDescription(std::string);
        void setAllFields  (std::string,
                            std::string,
                            std::string);

        //user's interface
        void show();
        void edit();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(const std::string&);

        //members
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
    this->label_       = "Buffer";
    this->name_        = "New Task";
    this->description_ = "New Task";
    this->id_          = -1;
    this->version_     = 1;

    numberOfNotes++;

}

Note::Note(std::string name,
            std::string description = "New Note",
            std::string label = "Buffer") {

    this->label_       = label;
    this->name_        = name;
    this->description_ = description;
    this->id_          = -1;
    this->version_     = 1;

    numberOfNotes++;
}


Note::Note(const Note& right) {
    this->label_       = right.label_;
    this->name_        = right.name_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
}

Note::Note(Note&& right) {
    this->label_       = right.label_;
    this->name_        = right.name_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
}

Note::~Note() {
    numberOfNotes--;
}

Note& Note::operator=(const Note& other) {
    if (this == &other) {
        return *this;
    }

    this->label_       = other.label_;
    this->name_        = other.name_;
    this->description_ = other.description_;
    this->version_     = other.version_;
    this->id_          = other.id_;

    return *this;
}

Note& Note::operator=(Note&& right) {

    if (this == &right) {
        return *this;
    }

    this->label_       = right.label_;
    this->name_        = right.name_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

    return *this;
}

std::size_t Note::getNumberOfNotes() {
    return Note::numberOfNotes;
}

void Note::setLabel(std::string label) {
    this->label_ = label;
    this->updateVersion();
}

void Note::setName(std::string name) {
    this->name_ = name;
    this->updateVersion();
}

void Note::setDescription(std::string description) {
    this->description_ = description;
    this->updateVersion();
}

void Note::setAllFields(std::string name,
                        std::string description = "New Note",
                        std::string label       = "Buffer") {

    this->name_        = name;
    this->description_ = description;
    this->label_       = label;
    this->updateVersion();
}

void Note::show() {
    std::cout << std::setw(13) << "Label: ";
    std::cout << "#" << label_ << std::endl;

    std::cout << std::setw(13) << "Name: ";
    std::cout << name_ << std::endl;

    std::cout << std::setw(13) << "Description: ";
    std::cout << description_ << std::endl;

    std::cout << std::setw(13) << "id_: ";
    std::cout << id_ << std::endl;
}

void Note::edit() {
    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    this->show();

    std::string input;

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
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

        Day();
        Day(std::string);
        Day(const Day&);
        Day(Day&&);

        //operators
        friend bool operator==(const Day& left, const Day& right);
        Day& operator=(const Day&);
        Day& operator=(Day&&);

        //destructor
        ~Day() = default;

        //setters
        void setDate(std::string);
        void addDeal(Deal);
        void addImportant(Important);

        //user's interface
        void removeDeal(int);
        void editDeal(int);

        void removeImportant(int);
        void editImportant(int);

        void showDeals();
        void showImportants();

        void show();
        void edit();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(const std::string&);

        //members
        std::string date_;
        std::vector<Deal> deals_;           //#include <Deal.h>
        std::vector<Important> importants_; //#include <Impportant.h>
};

bool operator==(const Day& left, const Day& right) {
    return (left.date_       == right.date_)   &&
           (left.deals_      == right.deals_) &&
           (left.importants_ == right.importants_) &&
           (left.version_    == right.version_);
}

Day::Day()
{
	this->date_    = "01 January 1970";
    this->id_      = -1;
    this->version_ = 1;
}

Day::Day(std::string date) {
    this->date_    = date;
    this->id_      = -1;
    this->version_ = 1;
}

Day::Day(const Day& other) {
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
    this->id_         = other.id_;
}
Day::Day(Day&& other) {
    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
    this->id_         = other.id_;
}
Day& Day::operator=(const Day& other) {

    if (this == &other) {
        return *this;
    }

    this->date_       = other.date_;
    this->deals_      = other.deals_;
    this->importants_ = other.importants_;
    this->version_    = other.version_;
    this->id_         = other.id_;

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
    this->id_         = other.id_;

    return *this;
}


void Day::setDate(std::string date) {
    this->date_ = date;
    this->updateVersion();
}

void Day::addDeal(Deal deal) {
    this->deals_.push_back(deal);
    (this->deals_.end()-1)->setDate(this->date_);
}

void Day::addImportant(Important important) {
    this->importants_.push_back(important);
}

void Day::removeDeal(int pos) {
    pos--;
    auto it = this->deals_.begin() + pos;
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
}

void Day::removeImportant(int pos) {
	pos--;
    auto it = this->importants_.begin() + pos;
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
}

void Day::showDeals() {
    int i = 1;
    for (auto &j : deals_) {
        std::cout << i << ". " << std::endl;
        j.show();
        i++;
    }
}

void Day::showImportants() {
    int i = 1;
    for (auto &j : importants_) {
        std::cout << i << ". " << j.important_ << std::endl;
        i++;
    }
}

void Day::show() {
    std::cout << std::setw(13) << "Date: ";
    std::cout<< date_ << std::endl;
    this->showDeals();
    this->showImportants();
}

void Day::edit() {

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    this->show();

    std::string input;

    std::cout << std::setw(13) << "Date: " << std::endl;
    std::getline(std::cin, input, '\n');
    if (input.size() > 1) {
        this->date_ = input;
        input.clear();
    }

    std::cout << std::setw(13) << "Deals: " << std::endl;
    if (!deals_.empty()) {
        for (auto it = deals_.begin(); it != deals_.end(); ++it) {
            it->edit();
        }
    }

    std::cout << std::setw(13) << "Importants: " << std::endl;

    if(!(importants_.empty())){
        for (auto it = importants_.begin(); it != importants_.end(); ++it) {
            it->edit();
        }
    }

    std::cout << std::endl;

    std::cout << std::endl;
    this->updateVersion();
}

std::string Day::concatenate() {

    //preprocessing important
    std::string tmp = importants_.begin()->important_;
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp = SEPARATOR + it->important_;
    }

    return (date_               +SEPARATOR+
            std::to_string(id_) +
            tmp);
}

void Day::deconcatenate(const std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    date_ = v[0];
    id_   = std::stoi(v[1]);

    //get importants
    for (int i = 2; i != v.size(); i++) {
        Important important(v[i]);
        important.date_ = this->date_;
        this->importants_.push_back(important);
    }
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

                                    make_column("Impportant",
                                        &Important::important_),

                                    make_column("Date",
                                        &Important::date_ )),

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

                                    make_column("Date",
                                        &Deal::date_),

                                    make_column("Begin",
                                        &Deal::begin_),

                                    make_column("End",
                                        &Deal::end_)),

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

using Storage = decltype(initLocalDb(""));

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {}

  void start()
  {
    do_read();
  }

    std::string name;
    std::string databaseName;
    std::shared_ptr<Storage> localDb = nullptr;

    std::vector<Task> tasks_;
    std::vector<Note> notes_;
    std::vector<Deals> deals_;
    std::vector<Day> days_;

    void getDataFromLocalBase();

    void processData();

    void send();
    void receive();
    void process();

    void sendDeals();
    void sendDays();
    void sendTasks();
    void sendNotes();

    void receiveUser();
    void receiveDeals();
    void receiveDays();
    void receiveTasks();
    void receiveNotes();

    void processDeals();
    void processDays();
    void processTasks();
    void processNotes();

private:
    tcp::socket socket_;
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(!data_.compare("Begin")) {
                this->processData();
            }
          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  enum { max_length = 1024 };
  std::string data_;
};

void session::processData() {

    while(!(!data_.compare("End"))) {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(!data_.compare("BeginUser")) {
                this->receiveUser();
                this->databaseName = this->name + ".sqlite";
                this->localDb = std::make_shared<Storage>(initLocalDb(std::string(this->databaseName)));
                this->localDb->sync_schema();
                this->makeBackup();
            }
            else if (!data_.compare("BeginTasks")) {
                this->receiveTasks();
            }
            else if (!data_.compare("BeginNotes")) {
                this->receiveNotes();
            }
            else if (!data_.compare("BeginDeals")) {
                this->receiveDeals();
            }
            else if (!data_.compare("BeginDays")) {
                this->receiveDays();
            }
          }
        });
    }
    this->process();
    this->send();


}

void session::receiveUser() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndUser"))) {
                this->name = data_;
            }
          }
        });
}

void session::makeBackup() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->databaseName;
    std::filesystem::copy_file(this->databaseName, path, std::filesystem::copy_options::overwrite_existing);
}

void session::receiveTasks() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndTasks"))) {
                Task task;
                task.deconcatenate(data_);
                this->tasks_.push_back(task);
            }
          }
        });
}

void session::receiveNotes() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndNotes"))) {
                Note note;
                note.deconcatenate(data_);
                this->notes_.push_back(task);
            }
          }
        });
}

void session::receiveDeals() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndDeals"))) {
                Deal deal;
                deal.deconcatenate(data_);
                this->deals_.push_back(task);
            }
          }
        });
}

void session::receiveDays() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndDays"))) {
                Day day;
                day.deconcatenate(data_);
                this->deals_.push_back(day);
            }
          }
        });
}

void session::processDeals() {

}
void session::processDays() {

}
void session::processTasks() {

}
void session::processNotes() {

}

void session::process() {
    this->processDeals();
    this->processDays();
    this->processTasks();
    this->processNotes();
}

void session::sendDeals() {

}
void session::sendDays() {

}
void session::sendTasks() {

}
void session::sendNotes() {

}
void session::send() {
    this->sendDeals();
    this->sendDays();
    this->sendTasks();
    this->sendNotes();
}
class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
