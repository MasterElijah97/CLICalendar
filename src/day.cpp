#include "day.h"

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
    this->version_ = other.version;
}
Day::Day(Day&& other) {
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version;
}
Day& Day::operator=(const Day& other) {
    if (this = &other) {
        return *this
    }
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version;
    return *this;
}
Day& Day::operator=(Day&& other) {
    if (this = &other) {
        return *this
    }
    this->date_ = other.date_;
    this->deals_ = other.deals_;
    this->importants_ = other.importants_;
    this->version_ = other.version;
    return *this;

}


void Day::setDate(std::string date) {
    this->date_ = std::move(date);
    this->updateVersion();
    this->base_->update(*this);

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
    this->base_->remove<Deal>(it->id_);
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
    this->base_->update(*it);
}

void Day::removeImportant(int pos) {
	pos--;
    auto it = this->importants_.begin() + pos;
    this->base_->remove<Important>(it->id_);
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
    this->base_->update(*it);
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
        std::cout << i << ". " << *it << std::endl;
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
            *it = input;
            input.clear();
        }
    }
            
    std::cout << std::endl;

    this->updateVersion();
    this->base_->update(*this);
}        

std::string Day::concatenate() {
    std::string tmp;
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp += *it;
    }
    return (date_                 +SEPARATOR+
        std::to_string(uniqueId_) +SEPARATOR+
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
                uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
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