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

class Task : public IVersion, public IUniqueId, public IDatabase {
    public:

        //constructors
        Task();
        Task(std::string);
        Task(const Task&);
        Task(Task&&);
        //destructors
        ~Task();
        //operators
        friend bool operator==(const Task& left, const Task& right);

        Task& operator=(const Task&);
        Task& operator=(Task&&);
        //getters
        bool getIsCompleted() const;
        std::string getDescription() const;
        std::size_t getVersion() const;
        std::size_t getUniqueId() const;
        static std::size_t getNumberOfTasks() const;
        //setters
        void setIsCompleted(const bool);
        void setDescription(const std::string);
        void setAllFields(const std::string,
                          const bool);
        //clearing
        void clearDescription();
        //funcs
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        bool isCompleted_;
        std::string description_;
        
    private:
        static std::size_t numberOfTasks;
};

std::size_t Task::numberOfTasks = 0;

bool operator==(const Task& left, const Task& right) {
    return (left.getDescription() == right.getDescription()) &&
           (left.getIsCompleted() == right.getIsCompleted()) &&
           (left.getVersion() == right.getVersion());
}

#endif // TASK_H
