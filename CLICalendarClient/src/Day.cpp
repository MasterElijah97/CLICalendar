#include "Day.h"

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

    this->importants_.reserve(100);
}

Day::Day(std::string date) {
    this->date_    = date;
    this->id_      = -1;
    this->version_ = 1;

    this->importants_.reserve(100);
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

void Day::updateVersion() {
    this->version_++;
}

void Day::setDate(const std::string& date) {
    this->date_ = date;
    this->updateVersion();
}

void Day::addDeal(const Deal& deal) {
    this->deals_.push_back(deal);
    (this->deals_.end()-1)->setDate(this->date_);
}

void Day::addImportant(const Important& important) {
    this->importants_.push_back(important);
}

void Day::removeDeal(std::size_t& pos) {
    pos--;
    auto it = this->deals_.begin() + pos;
    this->deals_.erase(it);
}

void Day::editDeal(std::size_t& pos) {
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

void Day::removeImportant(std::size_t& pos) {
	pos--;
    auto it = this->importants_.begin() + pos;
    this->importants_.erase(it);
}

void Day::editImportant(std::size_t& pos) {
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
    std::cout << date_ << std::endl;
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

    if(!importants_.empty()){
        for (auto it = importants_.begin(); it != importants_.end(); ++it) {
            it->edit();
        }
    }

    std::cout << std::endl;

    std::cout << std::endl;
    this->updateVersion();
}

std::string Day::concatenate() {

    if (this->importants_.empty()) {
        std::cout << date_ +SEPARATOR+ std::to_string(id_) << std::endl;
        return (date_ +SEPARATOR+ std::to_string(id_));
    }
    //preprocessing important
    std::string tmp;
    tmp.clear();

    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp += SEPARATOR + it->important_;
    }

    return (date_               +SEPARATOR+
            std::to_string(id_) +
            tmp);
}

void Day::deconcatenate(std::string msg) {
    std::cout << msg << std::endl;
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    date_ = v[0];
    id_   = std::stoi(v[1]);

    //get importants
    if (v.size() > 2){
        for (std::size_t i = 2; i != v.size(); i++) {
            Important important(v[i]);
            important.date_ = this->date_;
            this->importants_.push_back(important);
        }
    }
}
