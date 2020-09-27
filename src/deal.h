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
        std::string getName() const;
        std::string getDescription() const;
        std::string getLabel() const;
        std::string getPriority() const;
        std::string getBegin() const;
        std::string getEnd() const;
        std::pair< std::string, std::string > getTime() const;

        //setters

        void setName(std::string, base_t*);
        void setDescription(std::string), base_t*;
        void setLabel(std::string, base_t*);
        void setPriority(std::string);
        void setTime(std::string, std::string), base_t*;
        void setDate(std::string, base_t*);
       
        void edit(base_t*);

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
    return (left.getName()        == right.getName())        &&
           (left.getDescription() == right.getDescription()) &&
           (left.getLabel()       == right.getLabel())       &&
           (left.getPriority()    == right.getPriority())    &&
           (left.getTime()        == right.getTime())        &&
           (left.getVersion()     == right.getVersion());
}
#endif // DEAL_H
