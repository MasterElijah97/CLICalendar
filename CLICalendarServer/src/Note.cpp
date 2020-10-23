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

void Note::deconcatenate(std::string msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    label_       = v[0];
    name_        = v[1];
    version_     = std::stoi(v[2]);
    id_          = std::stoi(v[3]);
    description_ = v[4];
}

std::size_t Note::numberOfNotes = 0;
