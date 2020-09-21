#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

const std::string SEPARATOR(3, '&');

template<class... Ts>
class Task : public IVersion, public IUniqueId {
    public:

    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);
        //constructors
        Task() {
            isCompleted_ = false;
            description_ = "New Task";
            numberOfTasks++;
        }

        Task(std::string description) {
            isCompleted_ = false;
            description_ = description;
            numberOfTasks++;
        }


        Task(const Task& right) {
            isCompleted_ = right.getIsCompleted();
            description_ = right.getDescription();
            version_ = right.getVersion();
            numberOfTasks++;
        }

        Task(Task&& right) {
            isCompleted_ = right.getIsCompleted();
            description_ = right.getDescription();
            version_ = right.getVersion();

            right.clearDescription();
        }
        //destructors
        ~Task() {
            numberOfTasks--;
        }
        //operators
        friend bool operator==(const Task& left, const Task& right);

        Task& operator=(const Task& other) {
            if (this == &other) {
                return *this;
            }
            isCompleted_ = other.getIsCompleted();
            description_ = other.getDescription();
            version_ = other.getVersion();

            return *this;
        }

        Task& operator=(Task&& other) {
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
        bool getIsCompleted() const {
            return isCompleted_;
        }

        std::string getDescription() const {
            return description_;
        }

        friend const std::size_t getNumberOfTasks();

        std::size_t getVersion() const {
            return version_;
        }

        std::size_t getUniqueId() const {
            return uniqueId_;
        }

        //setters
        void setIsCompleted(const bool isCompleted) {
            isCompleted_ = isCompleted;
            updateVersion();
        }

        void setDescription(const std::string description) {
            description_ = description;
            updateVersion();
        }

        void setAllFields(const std::string description = "New Task",
                          const bool isCompleted = false) {
            isCompleted_ = isCompleted;
            description_ = description;
            updateVersion();
        }

        //clearing
        void clearDescription() {
            description_.clear();
        }
        //funcs
        void show() {
            if (isCompleted_) {
                std::cout << "Completed" << std::endl;
            } else {
                std::cout << "Uncompleted" << std::endl;
            }
            std::cout << description_ << std::endl;
        }

        std::string concatenate() {
            return std::to_string(uniqueId_)    +SEPARATOR+
                   std::to_string(version_)     +SEPARATOR+
                   std::to_string(isCompleted_) +SEPARATOR+
                   description_;
        }

        void deconcatenate(const std::string& msg) {
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
    private:
        bool isCompleted_;
        std::string description_;

        static std::size_t numberOfTasks;
};

std::size_t Task::numberOfTasks = 0;
const std::size_t getNumberOfTasks() {
            return Task::numberOfTasks;
}

bool operator==(const Task& left, const Task& right) {
    return (left.getDescription() == right.getDescription()) &&
           (left.getIsCompleted() == right.getIsCompleted()) &&
           (left.getVersion() == right.getVersion());
}

#endif // TASK_H
