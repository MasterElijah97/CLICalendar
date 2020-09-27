#include "note.h"

Note::Note() {
    label_ = "Buffer";
    name_ = "New Task";
    description_ = "New Task";

    numberOfNotes++;

}

Note::Note(std::string name,
    std::string description = "New Note",
    std::string label = "Buffer") {
    label_ = label;
    name_ = name;
    description_ = description;

    numberOfNotes++;
}


Note::Note(const Note& right) {
    label_ = right.getLabel();
    name_ = right.getName();
    description_ = right.getDescription();
    version_ = right.getVersion();
}

Note::Note(Note&& right) {
    label_ = right.getLabel();
    name_ = right.getName();
    description_ = right.getDescription();
    version_ = right.getVersion();


    right.clearLabel();
    right.clearName();
    right.clearDescription();
}
        //destructors
Note::~Note() {
    numberOfNotes--;
}
        //operators
Note& Note::operator=(const Note& other) {
    if (this == &other) {
        return *this;
    }

    label_ = other.getLabel();
    name_ = other.getName();
    description_ = other.getDescription();
    version_ = other.getVersion();

    return *this;
}

Note& Note::operator=(Note&& right) {
    if (this == &right) {
        return *this;
    }
    label_ = right.getLabel();
    name_ = right.getName();
    description_ = right.getDescription();
    version_ = right.getVersion();

    right.clearLabel();
    right.clearName();
    right.clearDescription();

    return *this;
}
        //getters
std::string Note::getLabel() const {
    return label_;
}

std::string Note::getName() const {
    return name_;
}

std::string Note::getDescription() const {
    return description_;
}

std::size_t Note::getNumberOfNotes() const  {
    return Note::numberOfNotes;
}
        //setters
void Note::setLabel(base_t* base, std::string label) {
    this->label_ = std::move(label);
    this->updateVersion();
    base->update(*this);
}

void Note::setName(base_t* base, std::string name) {
    this->name_ = std::move(name);
    this->updateVersion();
    base->update(*this);
}

void Note::setDescription(base_t* base, std::string description) {
    this->description_ = std::move(description);
    this->updateVersion();
    base->update(*this);
}

void Note::setAllFields(base_t* base, std::string name,
                  std::string description = "New Note",
                  std::string label = "Buffer") {
    this->name_ = std::move(name);
    this->description_ = std::move(description);
    this->label_ = std::move(label);
    this->updateVersion();
    base->update(*this);
}
        //clearing
void Note::clearName() {
    this->name_.clear();
}

void Note::clearDescription() {
    this->description_.clear();
}

void Note::clearLabel() {
    this->label_.clear();
}
        //funcs
void Note::show() {
    std::cout << "#" << label_ << std::endl;
    std::cout << name_ << std::endl;
    std::cout << description_ << std::endl;
}

void Note::edit(base_t* base) {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Label: ";
    std::cin >> input;
    if (!input.empty()) {
        this->label_ = input;
        input.clear();
    }

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

    std::cout << std::endl;

    this->updateVersion();
    base->update(*this);
}


std::string Note::concatenate() {
    return label_                    +SEPARATOR+
           name_                     +SEPARATOR+
           std::to_string(version_)  +SEPARATOR+
           std::to_string(uniqueId_) +SEPARATOR+
           description_;
}

void Note::deconcatenate(const std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;
    for (std::size_t i = 0; i != msg.size(); ++i) {
    if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
               	label_ = msg.substr(posBegin, i-1);
                posBegin = i+SEPARATOR.size();
            } else if (counter == 1) {
                counter++;
                name_ = msg.substr(posBegin, i-1);
                posBegin = i+SEPARATOR.size();
            } else if (counter == 2) {
                counter++;
                version_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 3) {
                counter++;
                uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            }
        }
    }
    description_ = msg.substr(posBegin);
}
