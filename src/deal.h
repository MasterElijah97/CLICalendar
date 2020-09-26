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

class Deal : public IVersion, public IUniqueId {
    public:
            template<class... Ts>
    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);
        //constructors
        Deal() {
            name_ = "New Deal";
            description_ = "New Deal";
            label_ = "My Deals";
            priority_ = "A";
            thisTime.begin = "0000";
            thisTime.end = "0100";
        }

        Deal(std::string name,
             std::string description = "No description",
             std::string label = "My Deals",
             std::string priority = "A",
             std::string begin = "0000",
             std::string end = "0000") {
            name_ = name;
            description_ = description;
            label_ = label;
            priority_ = priority;
            thisTime.begin = begin;
            thisTime.end = end;
        }

        Deal(const Deal& other) {
            name_ = other.getName();
            description_ = other.getDescription();
            label_ = other.getLabel();
            priority_ = other.getPriority();
            thisTime.begin = other.getBegin();
            thisTime.end = other.getEnd();
            version_ = other.getVersion();
        }

        Deal(Deal&& other) {
            name_ = other.getName();
            description_ = other.getDescription();
            label_ = other.getLabel();
            priority_ = other.getPriority();
            thisTime.begin = other.getBegin();
            thisTime.end = other.getEnd();
            version_ = other.getVersion();

            other.clearName();
            other.clearDescription();
            other.clearLabel();
            other.clearPriority();
            other.clearTime();
        }
        //operators
        friend bool operator==(const Deal& left, const Deal& right);

        Deal& operator=(const Deal& other) {
            if (this == &other) {
                return *this;
            }
            name_ = other.getName();
            description_ = other.getDescription();
            label_ = other.getLabel();
            priority_ = other.getPriority();
            thisTime.begin = other.getBegin();
            thisTime.end = other.getEnd();
            version_ = other.getVersion();

            return *this;
        }

        Deal& operator=(Deal&& other) {
            if (this == &other) {
                return *this;
            }
            name_ = other.getName();
            description_ = other.getDescription();
            label_ = other.getLabel();
            priority_ = other.getPriority();
            thisTime.begin = other.getBegin();
            thisTime.end = other.getEnd();
            version_ = other.getVersion();

            other.clearName();
            other.clearDescription();
            other.clearLabel();
            other.clearPriority();
            other.clearTime();

            return *this;
        }
        //destructor
        ~Deal() {

        }
        //clearing
        void clearName() {
            name_.clear();
        }

        void clearDescription() {
            description_.clear();
        }

        void clearLabel() {
            label_.clear();
        }

        void clearPriority() {
            priority_.clear();
        }

        void clearTime() {
            thisTime.begin.clear();
            thisTime.end.clear();
        }
        //getters
        std::string getName() const {
            return name_;
        }

        std::string getDescription() const{
            return description_;
        }

        std::string getLabel() const{
            return label_;
        }

        std::string getPriority() const{
            return priority_;
        }

        std::string getBegin() const{
            return thisTime.begin;
        }

        std::string getEnd() const{
            return thisTime.end;
        }

        std::pair< std::string, std::string > getTime() const {
            auto time = std::make_pair(thisTime.begin, thisTime.end);
            return time;
        }

        //setters

        void setName(std::string name) {
            name_ = name;
            updateVersion();
        }

        void setDescription(std::string description) {
            description_ = description;
            updateVersion();
        }

        void setLabel(std::string label) {
            label_ = label;
            updateVersion();
        }

        void setPriority(std::string priority) {
            priority_ = priority;
            updateVersion();
        }

        void setTime(std::string begin, std::string end) {
            thisTime.begin = begin;
            thisTime.end = end;
            updateVersion();
        }

        void setDate(std::string date) {
            this->date_ = date;
            updateVersion();
        }

        void show() {
            //todo formatting time
            std::cout << thisTime.begin.substr(0, 1) << ":" << thisTime.begin.substr(3, 4)
                      << "-"
                      << thisTime.end.substr(0, 1)  << ":" << thisTime.end.substr(3, 4)
                      << std::endl;
            std::cout << "#" << label_ << std::endl;
            std::cout << priority_ << std::endl;
            std::cout << name_ << std::endl;
            std::cout << description_ << std::endl;
        }

        void edit(base_t* base) {
            std::string input;

            this->show();

            std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

            std::cout << "Name: ";
            std::cin >> input;
            if (!input.empty()) {
                this->name_ = input;
                input.clear();
            }

            std::cout << "Description: ";
            std::cin >> input;
            if (!input.empty()) {
                this->description_ = input;
                input.clear();
            }

            std::cout << "Label: ";
            std::cin >> input;
            if (!input.empty()) {
                this->label_ = input;
                input.clear();
            }

            std::cout << "Priority: ";
            std::cin >> input;
            if (!input.empty()) {
                this->priority_ = input;
                input.clear();
            }

            std::cout << "Begins at ";
            std::cin >> input;
            if (!input.empty()) {
                this->thisTime.begin = input;
                input.clear();
            }

            std::cout << "Ends at ";
            std::cin >> input;
            if (!input.empty()) {
                this->thisTime.end = input;
                input.clear();
            }

            std::cout << std::endl;

            base->update(*this);
        }

        std::string concatenate() {
            return thisTime.begin            +SEPARATOR+
                   thisTime.end              +SEPARATOR+
                   name_                     +SEPARATOR+
                   label_                    +SEPARATOR+
                   priority_                 +SEPARATOR+
                   std::to_string(version_)  +SEPARATOR+
                   std::to_string(uniqueId_) +SEPARATOR+
                   description_;
        }

        void deconcatenate(std::string& msg) {
            std::size_t counter = 0;
            std::size_t posBegin = 0;

            for (std::size_t i = 0; i != msg.size(); ++i) {

                if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
                    if (counter == 0) {
                        counter++;
                        thisTime.begin = msg.substr(posBegin, i-1);
                        posBegin = i+3;
                    } else if (counter == 1) {
                        counter++;
                        thisTime.end = msg.substr(posBegin, i-1);
                        posBegin = i+3;
                    } else if (counter == 2) {
                        counter++;
                        name_ = msg.substr(posBegin, i-1);
                        posBegin = i+3;
                    } else if (counter == 3) {
                    counter++;
                        label_ = msg.substr(posBegin, i-1);
                        posBegin = i+3;
                    } else if (counter == 4) {
                        counter++;
                        priority_ = msg.substr(posBegin, i-1);
                        posBegin = i+3;
                    } else if (counter == 5) {
                        counter++;
                        version_ = std::stoi(msg.substr(posBegin, i-1));
                        posBegin = i+3;
                    } else if (counter == 6) {
                        counter++;
                        uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                        posBegin = i+3;
                    }
                }
            }
            description_ = msg.substr(posBegin);
        }

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
