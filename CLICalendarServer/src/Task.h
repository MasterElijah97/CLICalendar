#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "SEPARATOR.h"
#include "split.h"

class Task {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;

        Task();
        Task(std::string);
        Task(const Task&);
        Task(Task&&);

        //operators
        friend bool operator==(const Task& left, const Task& right);
        Task& operator=(const Task&);
        Task& operator=(Task&&);

        //destructor
        ~Task();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string);

        //members
        bool isCompleted_;
        std::string description_;
};

bool operator==(const Task&, const Task&);

#endif // TASK_H
