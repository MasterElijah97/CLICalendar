#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "SEPARATOR.h"
#include "split.h"

class Deal {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;

        Deal();

        Deal(std::string,
             std::string,
             std::string,
             std::string,
             std::string,
             std::string);

        Deal(const Deal&);

        Deal(Deal&&);

        //operators
        friend bool operator==(const Deal& left, const Deal& right);
        Deal& operator=(const Deal&);
        Deal& operator=(Deal&&);

        //destructor
        ~Deal() = default;
        
        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string);

        //members
        std::string date_;        //need to associating with Day  in databases
        std::string name_;
        std::string description_;
        std::string label_;
        std::string priority_;
        std::string begin_;       //begin deal at
        std::string end_;         //end deal at

};

bool operator==(const Deal&, const Deal&);
#endif // DEAL_H
