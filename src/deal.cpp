#include "deal.h"

Deal::Deal() {
    description_ = "New Deal";
    name_ = "New Deal";
    label_ = "My Deals";
    priority_ = "A";
    thisTime.begin = "0000";
    thisTime.end = "0100";
}

Deal::Deal(std::string name,
     std::string description = "No description",
     std::string label = "My Deals",
     std::string priority = "A",
     std::string begin = "0000",
     std::string end = "0000") {
    name_ = name;
    description_ = description;
    label_ = label;
    priority_ = priority;
    thisTime.begin = begin;
    thisTime.end = end;
}

Deal::Deal(const Deal& other) {
    name_ = other.getName();
    description_ = other.getDescription();
    label_ = other.getLabel();
    priority_ = other.getPriority();
    thisTime.begin = other.getBegin();
    thisTime.end = other.getEnd();
    version_ = other.getVersion();
}

Deal::Deal(Deal&& other) {
    name_ = other.getName();
    description_ = other.getDescription();
    label_ = other.getLabel();
    priority_ = other.getPriority();
    thisTime.begin = other.getBegin();
    thisTime.end = other.getEnd();
    version_ = other.getVersion();

    other.clearName();
    other.clearDescription();
    other.clearLabel();
    other.clearPriority();
    other.clearTime();
}
//operators
friend bool operator==(const Deal& left, const Deal& right);

Deal& Deal::operator=(const Deal& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.getName();
    description_ = other.getDescription();
    label_ = other.getLabel();
    priority_ = other.getPriority();
    thisTime.begin = other.getBegin();
    thisTime.end = other.getEnd();
    version_ = other.getVersion();

    return *this;
}

Deal& Deal::operator=(Deal&& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.getName();
    description_ = other.getDescription();
    label_ = other.getLabel();
    priority_ = other.getPriority();
   	thisTime.begin = other.getBegin();
    thisTime.end = other.getEnd();
    version_ = other.getVersion();

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
    thisTime.begin.clear();
    thisTime.end.clear();
}
//getters
std::string Deal::getName() const {
    return this->name_;
}

std::string Deal::getDescription() const{
    return this->description_;
}

std::string Deal::getLabel() const{
    return this->label_;
}

std::string Deal::getPriority() const{
    return this->priority_;
}

std::string getBegin() const{
    return this->thisTime.begin;
}

std::string getEnd() const{
    return this->thisTime.end;
}

std::pair< std::string, std::string > getTime() const {
    auto time = std::make_pair(this->thisTime.begin, 
    							this->thisTime.end);
    return time;
}

//setters

void setName(std::string name) {
    name_ = name;
    updateVersion();
    base_->update(*this);
}

void setDescription(std::string description) {
    description_ = description;
    updateVersion();
    base_->update(*this);
}

void setLabel(std::string label) {
    label_ = label;
    updateVersion();
    base_->update(*this);
}

void setPriority(std::string priority) {
    priority_ = priority;
    updateVersion();
    base_->update(*this);
}

void setTime(std::string begin, std::string end) {
    thisTime.begin = begin;
    thisTime.end = end;
    updateVersion();
    base_->update(*this);
}

void setDate(std::string date) {
    this->date_ = date;
    updateVersion();
    base_->update(*this);
}

void show() {
    //todo formatting time
    std::cout << thisTime.begin.substr(0, 1) << ":" << thisTime.begin.substr(3, 4)
              << "-"
              << thisTime.end.substr(0, 1)  << ":" << thisTime.end.substr(3, 4)
              << std::endl;
    std::cout << "#" << label_ << std::endl;
    std::cout << priority_ << std::endl;
    std::cout << name_ << std::endl;
    std::cout << description_ << std::endl;
}

void edit() {
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
        this->thisTime.begin = input;
        input.clear();
    }

    std::cout << "Ends at ";
    std::cin >> input;
    if (!input.empty()) {
        this->thisTime.end = input;
        input.clear();
    }

    std::cout << std::endl;
    this->updateVersion();
    base_->update(*this);
}

std::string concatenate() {
    return thisTime.begin            +SEPARATOR+
           thisTime.end              +SEPARATOR+
           name_                     +SEPARATOR+
           label_                    +SEPARATOR+
           priority_                 +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(uniqueId_) +SEPARATOR+
           description_;
}

void deconcatenate(std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;

    for (std::size_t i = 0; i != msg.size(); ++i) {

        if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
                thisTime.begin = msg.substr(posBegin, i-1);
                posBegin = i+3;
            } else if (counter == 1) {
                counter++;
                thisTime.end = msg.substr(posBegin, i-1);
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
                uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+3;
            }
        }
    }
    description_ = msg.substr(posBegin);
}
