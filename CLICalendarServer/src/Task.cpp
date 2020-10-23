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
    numberOfTasks++;
}

Task::Task(std::string description) {
    this->isCompleted_ = false;
    this->description_ = description;
    this->id_          = -1;
    this->version_     = 1;
    numberOfTasks++;
}


Task::Task(const Task& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
    numberOfTasks++;
}

Task::Task(Task&& right) {
    this->isCompleted_ = right.isCompleted_;
    this->description_ = right.description_;
    this->version_     = right.version_;
    this->id_          = right.id_;
}

Task::~Task() {
    numberOfTasks--;
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

void Task::setIsCompleted(const bool isCompleted) {
    this->isCompleted_ = isCompleted;
    this->updateVersion();
}

void Task::setDescription(const std::string description) {
    this->description_ = description;
    this->updateVersion();
}

void Task::setAllFields(const std::string description = "New Task",
                        const bool isCompleted = false) {

    this->isCompleted_ = isCompleted;
    this->description_ = description;
    this->updateVersion();
}

void Task::show() {
    if (isCompleted_) {
        std::cout << std::setw(13) << "Status: ";
        std::cout << "Completed" << std::endl;
    } else {
        std::cout << std::setw(13) << "Status: ";
        std::cout << "Uncompleted" << std::endl;
    }
    std::cout << std::setw(13) << "Description: ";
    std::cout << description_ << std::endl;

    std::cout << std::endl;
}

void Task::edit() {

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    this->show();

    std::string input;

    std::cout << std::setw(13) << "Description: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }


    std::cout << std::setw(13) << "Completed? [Y / N]: ";
    std::getline(std::cin, input, '\n');
    if (!input.empty()) {

        if ((input.find("Y") != std::string::npos) || (input.find("y") != std::string::npos)) {
            this->isCompleted_ = true;
        } else {
            this->isCompleted_ = false;
        }
        input.clear();

    }

    std::cout << std::endl;

    std::cout << std::endl;
    this->updateVersion();
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

std::size_t Task::numberOfTasks = 0;

std::size_t Task::getNumberOfTasks() {
    return Task::numberOfTasks;
}
