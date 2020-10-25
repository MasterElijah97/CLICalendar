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

std::string Day::concatenate() {

    if (this->importants_.empty()) {
        std::cout << date_ +SEPARATOR+ std::to_string(id_) << std::endl;
        return (date_ +SEPARATOR+ std::to_string(id_));
    }
    //preprocessing important
    std::string tmp = importants_.begin()->important_;
    for (auto it = importants_.begin(); it != importants_.end(); ++it) {
        tmp = SEPARATOR + it->important_;
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
