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

void Deal::deconcatenate(std::string msg) {
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

bool operator==(const Deal& left, const Deal& right) {
    return (left.name_          == right.name_)        &&
           (left.description_   == right.description_) &&
           (left.label_         == right.label_)       &&
           (left.priority_      == right.priority_)    &&
           (left.begin_         == right.begin_)       &&
           (left.end_           == right.end_)         &&
           (left.version_       == right.version_);
}
