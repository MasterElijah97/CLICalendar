#include "Deal.h"

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
    this->date_        = other.date_;
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
    this->date_        = other.date_;
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
    this->date_        = other.date_;

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
    this->date_        = other.date_;

    return *this;
}

void Deal::updateVersion() {
    this->version_++;
}

void Deal::setName(std::string name) {
    this->name_ = std::move(name);
    this->updateVersion();
}

void Deal::setDescription(std::string description) {
    this->description_ = std::move(description);
    this->updateVersion();
}

void Deal::setLabel(std::string label) {
    this->label_ = std::move(label);
    this->updateVersion();
}

void Deal::setPriority(std::string priority) {
    this->priority_ = std::move(priority);
    this->updateVersion();
}

void Deal::setTime(std::string begins, std::string ends) {
    this->begin_ = std::move(begins);
    this->end_ = std::move(ends);
    this->updateVersion();
}

void Deal::setDate(std::string date) {
    this->date_ = std::move(date);
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
    return date_                     +SEPARATOR+
           begin_                    +SEPARATOR+
           end_                      +SEPARATOR+
           name_                     +SEPARATOR+
           label_                    +SEPARATOR+
           priority_                 +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_)       +SEPARATOR+
           description_;
           
}

void Deal::deconcatenate(std::string msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    date_        = v[0];
    begin_       = v[1];
    end_         = v[2];
    name_        = v[3];
    label_       = v[4];
    priority_    = v[5];
    version_     = std::stoi(v[6]);
    id_          = std::stoi(v[7]);
    description_ = v[8];
}

bool operator==(const Deal& left, const Deal& right) {
    return (left.name_          == right.name_)        &&
           (left.description_   == right.description_) &&
           (left.label_         == right.label_)       &&
           (left.priority_      == right.priority_)    &&
           (left.begin_         == right.begin_)       &&
           (left.end_           == right.end_)         &&
           (left.version_       == right.version_);
}
