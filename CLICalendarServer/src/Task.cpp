#include "Task.h"

bool operator==(const Task& left, const Task& right) {
    return (left.description_ == right.description_) &&
           (left.isCompleted_ == right.isCompleted_) &&
           (left.version_     == right.version_);
}

Task::Task() {
    this->isCompleted_ = false;
    this->description_ = "New Task";
    this->id_          = -1;
    this->version_     = 1;

}

Task::Task(std::string description) {
    this->isCompleted_ = false;
    this->description_ = description;
    this->id_          = -1;
    this->version_     = 1;

}


Task::Task(const Task& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

}

Task::Task(Task&& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
}

Task::~Task() {

}

Task& Task::operator=(const Task& right) {
    if (this == &right) {
        return *this;
    }

    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

    return *this;
}

Task& Task::operator=(Task&& right) {
    if (this == &right) {
	    return *this;
    }

    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;

    return *this;
}

std::string Task::concatenate() {
    return std::to_string(id_)          +SEPARATOR+
           std::to_string(version_)     +SEPARATOR+
           std::to_string(isCompleted_) +SEPARATOR+
           description_;
}

void Task::deconcatenate(std::string msg) {
    std::vector<std::string> v = split(msg, SEPARATOR.c_str()[0]);
    id_          = std::stoi(v[0]);
    version_     = std::stoi(v[1]);
    isCompleted_ = std::stoi(v[2]);
    description_ = v[3];
}
