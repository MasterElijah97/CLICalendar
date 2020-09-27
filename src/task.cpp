#include "task.h"

Task::Task() {
    isCompleted_ = false;
    description_ = "New Task";
    numberOfTasks++;
}

Task::Task(std::string description) {
    isCompleted_ = false;
    description_ = description;
    numberOfTasks++;
}


Task::Task(const Task& right) {
    isCompleted_ = right.getIsCompleted();
    description_ = right.getDescription();
    version_ = right.getVersion();
    numberOfTasks++;
}

Task::Task(Task&& right) {
    isCompleted_ = right.getIsCompleted();
    description_ = right.getDescription();
    version_ = right.getVersion();

    right.clearDescription();
}
        //destructors
Task::~Task() {
    numberOfTasks--;
}

Task& Task::operator=(const Task& other) {
    if (this == &other) {
        return *this;
    }
    isCompleted_ = other.getIsCompleted();
    description_ = other.getDescription();
    version_ = other.getVersion();

    return *this;
}

Task& Task::operator=(Task&& other) {
    if (this == &other) {
	    return *this;
    }
    isCompleted_ = other.getIsCompleted();
    description_ = other.getDescription();
    version_ = other.getVersion();

    other.clearDescription();

    return *this;
}
        //getters
bool Task::getIsCompleted() const {
    return isCompleted_;
}

std::string Task::getDescription() const {
    return description_;
}

std::size_t Task::getVersion() const {
    return version_;
}

std::size_t Task::getUniqueId() const {
    return id_;
}

        //setters
void Task::setIsCompleted(const bool isCompleted) {
    isCompleted_ = isCompleted;
    updateVersion();
}

void Task::setDescription(const std::string description) {
    description_ = description;
    updateVersion();
}

void Task::setAllFields(const std::string description = "New Task",
                  const bool isCompleted = false) {
    isCompleted_ = isCompleted;
    description_ = description;
    updateVersion();
}

        //clearing
void Task::clearDescription() {
    description_.clear();
}
        //funcs
void Task::show() {
    if (isCompleted_) {
        std::cout << "Completed" << std::endl;
    } else {
        std::cout << "Uncompleted" << std::endl;
    }
    std::cout << description_ << std::endl;
}

void Task::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

    std::cout << "Description: ";
    std::cin >> input;
    if (!input.empty()) {
        this->description_ = input;
        input.clear();
    }


    std::cout << "Completed? [Y / N]: ";
    std::cin >> input;
    if (!input.empty()) {

        if ((input.find("Y") != std::string::npos) || (input.find("y") != std::string::npos)) {
            this->isCompleted_ = true;
        } else {
            this->isCompleted_ = false;
        }
        input.clear();
                
    }
            
    std::cout << std::endl;

    base_->update(*this);
}   

std::string Task::concatenate() {
    return std::to_string(uniqueId_)    +SEPARATOR+
           std::to_string(version_)     +SEPARATOR+
           std::to_string(isCompleted_) +SEPARATOR+
           description_;
}

void Task::deconcatenate(const std::string& msg) {
    std::size_t counter = 0;
    std::size_t posBegin = 0;

    for (std::size_t i = 0; i != msg.size(); ++i) {
        if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
            if (counter == 0) {
                counter++;
                uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 1) {
                counter++;
                version_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            } else if (counter == 2) {
                counter++;
                isCompleted_ = std::stoi(msg.substr(posBegin, i-1));
                posBegin = i+SEPARATOR.size();
            }
        }
    }
    description_ = msg.substr(posBegin);
}

std::size_t Task::getNumberOfTasks() const {
    return Task::numberOfTasks;
}