#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

#include "src/iversion.h"
#include "src/iuniqueid.h"

const std::string SEPARATOR(3, '&');

class Deal : public IVersion, public IUniqueId, public IDatabase {
    public:
        //constructors
        Deal();

        Deal(std::string,
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
        //clearing
        void clearName();
        void clearDescription();
        void clearLabel();
        void clearPriority();
        void clearTime();
        //getters

        //setters

        void setName(std::string);
        void setDescription(std::string);
        void setLabel(std::string);
        void setPriority(std::string);
        void setTime(std::string, std::string);
        void setDate(std::string);
       
        void edit();

        void show();

        std::string concatenate();

        void deconcatenate(std::string&);

        std::string name_;
        std::string description_;
        std::string label_;
        std::string priority_;
        std::string date_;
        struct Time {
            std::string begin;
            std::string end;
        } thisTime;
};

bool operator==(const Deal& left, const Deal& right) {
    return (left.name_          == right.name_)          &&
           (left.description_   == right.description_)   &&
           (left.label_         == right.label_)         &&
           (left.priority_      == right.priority_)      &&
           (left.thisTime.begin == right.thisTime.begin) &&
           (left.thisTime.end   == right.thisTime.end)   &&
           (left.version_       == right.version_);
}
#endif // DEAL_H
