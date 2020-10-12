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

void spaceFilter(std::string& input) {

    for(int i = 0; i < input.length()-1; i++) {

        if(input[i] == ' ' && input[i+1] == ' ') {
            input.erase(i,1);
            i--;
        }

    }
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
            std::to_string(id_) +SEPARATOR+
            tmp);
}

void Day::deconcatenate(const std::string& msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    date_ = v[0];
    id_   = std::stoi(v[1]);

    //get importants
    for (int i = 2; i != v.size(); i++) {
        Important important(v[i]);
        this->importants_.push_back(important);
    }
}

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
        //need to cipher data
        //will be in use in future
        int key_;
        void key_gen();
        std::string doCryptoMessage(std::string); //just XOR
};

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

//--------------------------------------------------------------
// allows to use type of storage in future
//--------------------------------------------------------------
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

using Accounts = decltype(initAccountsDb());
using Storage = decltype(initLocalDb(""));
//--------------------------------------------------------------

// pre-declaration
struct CommandChecker; //#include <CommandChecker.h>

class Session {
public:
        Session(std::shared_ptr<User>);
        Session() = default;
        Session(const Session&) = default;
        Session(Session&&) = default;
        Session& operator=(const Session&) = default;
        Session& operator=(Session&&) = default;

        ~Session() = default;

        friend CommandChecker;

        std::shared_ptr<User> user = nullptr;

        std::shared_ptr<Storage> localDb = nullptr;

        std::vector<Task> tasks_;
        std::vector<Note> notes_;
        std::vector<Day> days_;

        enum variantObserver {
            NOT_SETTED = 0,
            DAY_SETTED = 1,
            NOTE_SETTED = 2,
            TASK_SETTED = 3,
            DEAL_SETTED = 4,
            IMPORTANT_SETTED= 5
        };

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > joinedObject_;

        variantObserver joinedSetted = NOT_SETTED;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > copyableObject_;

        variantObserver copyableSetted = NOT_SETTED;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > moveableObject_;

        variantObserver moveableSetted = NOT_SETTED;

        void addTask(Task);
        void addNote(Note);
        void addDay(Day);

        void openTasks();
        void openNotes();
        void openDays();

        void showJoined();
        void showHelp();

        void editDeal(const int&);
        void editImportant(const int&);
        void editItem();

        void copyItem();
        void pasteItem();
        void moveItem();
        void pasteMoveableItem();

        void removeTask();
        void removeNote();
        void removeDay();
        void removeDeal(const int&);
        void removeImportant(const int&);

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
        void setJoined(std::vector<Important>::iterator);

        void setMovable();
        void setCopyable();

        void incrementJoined();
        void decrementJoined();

    private: //visitors

struct JoinedEditor {

    JoinedEditor(Session&);
    Session* session;
    ~JoinedEditor();

    template<typename T>
    void operator()(T&);
};


struct JoinedShower {
    template<typename T>
    void operator()(T&);
};



struct MoveablePaster {

    MoveablePaster(Session&);
    Session* session;
    ~MoveablePaster();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct CopyablePaster {

    CopyablePaster(Session&);
    Session* session;
    ~CopyablePaster();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct JoinedIncrementAllower {

    JoinedIncrementAllower(Session&);
    Session* session;
    ~JoinedIncrementAllower();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
	void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct JoinedDecrementAllower {

    JoinedDecrementAllower(Session&);
    Session* session;
    ~JoinedDecrementAllower();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct MoveableSetter {

	MoveableSetter(Session&);
	Session* session;
	~MoveableSetter();

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Important>::iterator&);
};

struct CopyableSetter {

    CopyableSetter(Session&);
    Session* session;
    ~CopyableSetter();

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Important>::iterator&);
};
};

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
     this->tasks_.push_back(task);
 }

 void Session::addNote(Note note) {
     this->notes_.push_back(note);
 }

 void Session::addDay(Day day) {
     this->days_.push_back(day);
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

 	std::cout << std::endl;

 	std::cout << "--Other--"                                                                                             << std::endl;
 	std::cout << "exit                      -sync bases, disconnect from server and log out"                             << std::endl;

 	std::cout << std::endl;
 }

 void Session::editDeal(const int& arg3) {

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

void Session::editImportant(const int& arg3) {
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

void Session::removeDeal(const int& arg3) {

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

void Session::removeImportant(const int& arg3) {

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
void Session::setJoined(std::vector<Important>::iterator it) {
   this->joinedObject_ = std::move(it);
}


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

Accounts accountsDb = initAccountsDb();

//Helper
//Asks login and password, checks them, change password
struct AccessProvider {
    AccessProvider(std::shared_ptr<User>);
    std::shared_ptr<User> user;
    void addingNewUser();
    void logIn();
    void logOut();
    void changePassword();
    void accessChecker(const std::string&, const std::string&);
private:
    void noechoInput(std::string&, char*);
};

void AccessProvider::noechoInput(std::string& password, char* msg = "Password: ") {
    //initializing c-style string
    const int MAX_PASSWORD_SIZE = 50;
    char str[MAX_PASSWORD_SIZE];
    for (int i = 0; i != 25; i++) {
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

    password = pass;
    //clear ncurses screen and close ncurses
    clear();
    endwin();
}

AccessProvider::AccessProvider(std::shared_ptr<User> user) {
    this->user = user;
}

void AccessProvider::addingNewUser() {
    std::string login;
    std::string password;
    std::cout << "Please, enter new login" << std::endl;
    std::getline(std::cin, login, '\n');

        std::vector<User> isUserExists = ::accountsDb.get_all<User>(where(is_equal(&User::login_, login)));

        if (isUserExists.empty()) {
            std::cout << "Please, enter new password" << std::endl;

            noechoInput(password);

            this->user->login_ = login;
            this->user->hashedPass_ = md5(password);

            auto insertedId = ::accountsDb.insert(*(this->user));
            this->user->id_ = insertedId;
            //::accountsDb.update(*user);

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

    auto ExistingUser = ::accountsDb.get_all<User>(where(is_equal(&User::login_, login) &&
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
    std::cout << "You've logged out" << std::endl;
}

void AccessProvider::changePassword() {

    std::string oldPassword;
    noechoInput(oldPassword, "\nPlease, enter old password: ");
    std::string hashedOldPassword = md5(oldPassword);

    auto userChecking = ::accountsDb.get_all<User>(where(is_equal(&User::login_, this->user->login_) &&
                                                         is_equal(&User::hashedPass_, hashedOldPassword)));

    if (!userChecking.empty()) {

        std::string newPasswordFirst;
        std::string newPasswordSecond;

        noechoInput(newPasswordFirst, "\n\nPlease, enter new password: ");

        noechoInput(newPasswordSecond, "\n\n\nPlease, enter new password again: ");

        //method 'compare' returns 0 if strings are fully equal
        if (!newPasswordFirst.compare(newPasswordSecond)) {

            this->user->hashedPass_ = md5(newPasswordFirst);
            ::accountsDb.remove<User>(this->user->id_);

            this->user->id_ = -1;
            auto insertedId = ::accountsDb.insert(*(this->user));
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

//Helper
//Used for connection with server, operations with it and handling problems with it
using boost::asio::ip::tcp;
class NetWorker : public boost::noncopyable {
    public:
        NetWorker() = delete;
        NetWorker(std::shared_ptr<Session>);

        void setIp(std::string);
        void setPort(std::string);

        void connect();
        void disconnect();
        void sync();

        //This is not a net-session
        //It is user's session in app
        std::shared_ptr<Session> thisSession;

        std::string ip_to_connect = "127.0.0.1";
        std::string port_to_connect = "2001";

        bool isConnected = false;

        boost::asio::io_service io_service;
        tcp::socket s;
        tcp::resolver resolver;
        boost::system::error_code ec;
};

NetWorker::NetWorker(std::shared_ptr<Session> session) : s(io_service), resolver(io_service) {
    this->thisSession = session;
}

void NetWorker::setIp(std::string ip) {
    this->ip_to_connect = ip;
}

void NetWorker::setPort(std::string port) {
    this->port_to_connect = port;
}

void NetWorker::connect() {
    try {
        boost::asio::connect(this->s, this->resolver.resolve(ip_to_connect, port_to_connect));
        std::cout << "Connection established" << std::endl;
        this->isConnected = true;
    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        std::cout << "Try:\n1.Check internet connection\n2.Check server" << std::endl;
        this->isConnected = false;
    }
}

void NetWorker::disconnect() {

    if (isConnected) {

        this->s.close(ec);
        if (ec) {
            std::cout << "Something went wrong with NetWorker" << std::endl;
            ec.clear();
        }

        std::cout << "Connection closed" << std::endl;

        this->isConnected = false;

    } else {
            std::cout << "There is no one connection established" << std::endl;
    }
}

void NetWorker::sync() {
    if (isConnected) {
        std::string tmp;
        auto Users = ::accountsDb.get_all<User>();
        try {
            tmp = "BeginUsers";
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()), ec);
            tmp.clear();

            for (auto &usr : Users) {
                tmp = usr.login_ + '`' + usr.hashedPass_;
                boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()), ec);
                tmp.clear();
            }

            tmp = "EndUsers";
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()), ec);
            tmp.clear();

        } catch(std::exception& ex) {
            std::cout << "Something went wrong" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
//Helper
//dialog between user and program after user is logged in
struct CommandChecker {
    CommandChecker(std::shared_ptr<Session>,
                   std::shared_ptr<AccessProvider>,
                   std::shared_ptr<NetWorker>);

    std::shared_ptr<Session> thisSession;
    std::shared_ptr<AccessProvider> accessProvider;
    std::shared_ptr<NetWorker> netWorker;

    void clearConsole();
    void commandMonitor(const std::string&,
                        const std::string&,
                        const int&);
};

CommandChecker::CommandChecker(std::shared_ptr<Session> session,
                               std::shared_ptr<AccessProvider> accessProvider,
                               std::shared_ptr<NetWorker> netWorker) {

    this->thisSession = session;
    thisSession->localDb->sync_schema();
    this->accessProvider = accessProvider;
    this->netWorker = netWorker;
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

        thisSession->incrementJoined();

    }
    else if (!arg1.compare("prev")) {

        thisSession->decrementJoined();

    }
    else if (!arg1.compare("edit") && !arg2.compare("deal")) {

        thisSession->editDeal(arg3);

    }
    else if (!arg1.compare("edit") && !arg2.compare("important")) {

        thisSession->editImportant(arg3);

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

        }  else if (!arg2.compare("important")){

            thisSession->creatingImportant();

        } else {
            std::cout << "Wrong command. Please, check 'help'" << std::endl;
        }

    }
    else if (!arg1.compare("edit")) {

        thisSession->editItem();

    }
    else if (!arg1.compare("copy")) {

        thisSession->copyItem();
    }
    else if (!arg1.compare("paste")) {

        thisSession->pasteItem();

    }
    else if (!arg1.compare("move")) {

        thisSession->moveItem();

    }
    else if (!arg1.compare("here")) {

        thisSession->pasteMoveableItem();

    }
    else if (!arg1.compare("remove")) {

        if (!arg2.compare("task")) {

            thisSession->removeTask();

        } else if (!arg2.compare("note")) {

            thisSession->removeNote();

        } else if (!arg2.compare("day")) {

            thisSession->removeDay();

        } else if (!arg2.compare("deal")) {

           thisSession->removeDeal(arg3);

        } else if (!arg2.compare("important")) {

            thisSession->removeImportant(arg3);

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }
    else if (!arg1.compare("open")) {

        if (!arg2.compare("tasks")) {

            thisSession->openTasks();

        } else if (!arg2.compare("notes")) {

            thisSession->openNotes();

        } else if (!arg2.compare("days")) {

            thisSession->openDays();

        } else {

            std::cout << "Wrong command. Please, check 'help'" << std::endl;
            std::cout << std::endl;

        }
    }

    else if (!arg1.compare("log")) {

        if (!arg2.compare("out")) {

            this->accessProvider->logOut();

        }

    }
    else if (!arg1.compare("connect")) {

        this->netWorker->connect();

    }
    else if ((!arg1.compare("disconnect"))) {

        this->netWorker->disconnect();

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
    else if (!arg1.compare("change")) {

        if (!arg2.compare("password")) {

            this->accessProvider->changePassword();

        } else {

            std::cout << "Wrong second argument: " << arg2 << std::endl;
            std::cout << "Did you mean 'password'? " << std::endl;

        }

    }
    else {
        std::cout << "Wrong command. Please, check 'help'" << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    accountsDb.sync_schema();
    auto user = std::make_shared<User>();
    //User user;
    auto accessProvider = std::make_shared<AccessProvider>(user);

    std::cout << "Welcome to CLICalendar. Please, log in or add new user" << std::endl;
    std::cout << "Write 'help' to get list of commands" << std::endl;
    std::cout << std::endl;

    while(1) {

        while (user->isLoggedIn() == false) {
            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');
            std::cout << std::endl;
            spaceFilter(input);

            std::vector<std::string> v = split(input, ' ');
            std::cin.clear();
            if ( v.size() == 1 ) {
                accessProvider->accessChecker(v[0], std::string(""));
            }
            else if ( v.size() == 2) {
                accessProvider->accessChecker(v[0], v[1]);
            }
            input.clear();
        }

        auto thisSession = std::make_shared<Session>(user);
        thisSession->localDb->sync_schema();

        boost::asio::io_service io_service;
        auto netWorker = std::make_shared<NetWorker>(thisSession);

        CommandChecker commandChecker(thisSession, accessProvider,  netWorker);

        while(user->isLoggedIn() == true) {

            std::cout << std::setw(13) << "Command: ";

            std::string input;

            std::getline(std::cin, input, '\n');
            spaceFilter(input);

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
