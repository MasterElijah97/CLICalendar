#include "day.h"

Day::Day()
{
	date_ = "01 January 1970";
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

Day::Day(const std::string date) {
    date_ = date;
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

std::string Day::getDate() const {
    return date_;
}

std::vector<Deal> Day::getDeals() const {
    return deals_;
}

std::vector<Impportant> Day::getImportants() const {
    return importants_;
}

void Day::setDate(std::string date, base_t* base) {
    date_ = date;
    this->updateVersion();
    base->update(*this);

}

void Day::addDeal(Deal deal) {
    deals_.emplace_back(deal);
    (deals_.end()-1)->setDate(date_);
}

void Day::addImportant(Important important) {
    importants_.emplace_back(important);
}

//todo -------------
void Day::removeDeal(int pos, base_t* base) {
    pos--;
    auto it = this->deals_.begin() + pos;
    base->remove<Deal>(it->id_);
    deals_.erase(it);
}

void Day::editDeal(int pos, base_t* base) {
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
    base->update(*it);
}

void Day::removeImportant(int pos, base_t* base) {
	pos--;
    auto it = this->importants_.begin() + pos;
    base->remove<Important>(it->id_);
    importants_.erase(it);
}

void Day::editImportant(int pos, base_t* base) {
    pos--;
    auto it = this->importants_.begin() + pos;
    std::cout << "Editing important..." << std::endl;
    std::cout << "Please, enter new important" << std::endl;
    std::string tmp;
    std::cin >> tmp;
    it->important_ = tmp;
    it->updateVersion();
    base->update(*it);
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
    showDeals();
    showImportants();
}

void Day::edit(base_t* base) {
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
            
    std::cout << std::endl;

    this->updateVersion();
    base->update(*this);
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