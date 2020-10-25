#include "Note.h"

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



}

Note::Note(std::string name,
            std::string description = "New Note",
            std::string label = "Buffer") {

    this->label_       = label;
    this->name_        = name;
    this->description_ = description;
    this->id_          = -1;
    this->version_     = 1;


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

std::string Note::concatenate() {
    return label_                    +SEPARATOR+
           name_                     +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(id_)       +SEPARATOR+
           description_;
}

void Note::deconcatenate(std::string msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    label_       = v[0];
    name_        = v[1];
    version_     = std::stoi(v[2]);
    id_          = std::stoi(v[3]);
    description_ = v[4];
}