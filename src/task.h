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

#include "include/sqlite_orm.h"

#include "src/black_magic.h"

#include "src/iversion.h"
#include "src/iuniqueid.h"
#include "src/idatabase.h"

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
        static std::size_t getNumberOfTasks();
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
    return (left.description_ == right.description_) &&
           (left.isCompleted_ == right.isCompleted_) &&
           (left.version_ == right.version_);
}

#endif // TASK_H
