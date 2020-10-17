#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include <SEPARATOR.h>
#include <split.h>

class Important {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion() {
            this->version_++;
        }

        Important();
        Important(std::string);
        Important(const Important&);
        Important(Important&&);

        //operators
        friend bool operator==(const Important& left, const Important& right);
        Important& operator=(const Important&);
        Important& operator=(Important&&);

        //destructor
        ~Important() = default;

        //setters
        void setImportant(std::string);
        void setDate(std::string);

        //user's interface
        void edit();
        void show();

        //members
        std::string important_;
        std::string date_;      //need to associating with Day  in databases
};

bool operator==(const Important&, const Important&);
#endif // IMPORTANT_H
