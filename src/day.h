#ifndef DAY_H
#define DAY_H

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
#include "src/day.h"

const std::string SEPARATOR(3, '&');

class Day : public IVersion, public IUniqueId {
        template<class... Ts>
    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);
    public:
        Day() {
            date_ = "01 January 1970";
            importants_.emplace_back("Nothing");
            deals_.emplace_back("Frist of All");
        }

        Day(const std::string date) {
            date_ = date;
            importants_.emplace_back("Nothing");
            deals_.emplace_back("Frist of All");
        }

        ~Day() {

        }

        friend bool operator==(const Day& left, const Day& right);

        std::string getDate() const {
            return date_;
        }

        std::vector<Deal> getDeals() const {
            return deals_;
        }

        std::vector<Impportant> getImportants() const {
            return importants_;
        }

        void setDate(std::string date) {
            date_ = date;
        }

        void addDeal(Deal deal) {
            deals_.emplace_back(deal);
            (deals_.end()-1)->setDate(date_);
        }

        void addImportant(std::string important) {
            importants_.emplace_back(important);
        }

        //todo -------------
        void removeDeal(int pos /*Deal& removeIt*/) {
            pos--;
            deals_.erase(deals_.begin()+pos);
            //std::remove(this->importants.begin(), this->importants.end(), removeIt)
            //todo
        }

        void editDeal(int pos) {
            pos--;
            std::cout << "Editing deal..." << std::endl;
            std::string tmp;
            std::cout << "Please, enter time in such format HH:MM-HH:MM" << std::endl;
            std::cin >> tmp;
            if (!tmp.empty()) {
                deals_[pos].setTime(tmp.substr(0, 1)+tmp.substr(3, 4), tmp.substr(6, 7)+tmp.substr(9, 10));
            }
            std::cout << "Please, enter label" << std::endl;
            std::cin >> tmp;
            if (!tmp.empty()) {
                deals_[pos].setLabel(tmp);
            }
            std::cout << "Please, enter priority" << std::endl;
            std::cin >> tmp;
            if (!tmp.empty()) {
                deals_[pos].setPriority(tmp);
            }
            std::cout << "Please, enter name" << std::endl;
            std::cin >> tmp;
            if (!tmp.empty()) {
                deals_[pos].setName(tmp);
            }
            std::cout << "Please, enter description" << std::endl;
            std::cin >> tmp;
            if (!tmp.empty()) {
                deals_[pos].setDescription(tmp);
            }
        }

        void removeImportant(int pos /*std::string& removeIt*/) {
            pos--;
            importants_.erase(importants_.begin()+pos);
            //std::remove(this->importants.begin(), this->importants.end(), removeIt)
            //todo
        }

        void editImportant(int pos) {
            pos--;
            std::cout << "Editing important..." << std::endl;
            std::cout << "Please, enter new important" << std::endl;
            std::string tmp;
            std::cin >> tmp;
            importants_[pos].replace(0, tmp.size(), tmp);
            //*(importants_.[pos]) = tmp;

        }
        //------------------
        //funcs
        void showDeals() {
            for (auto it = deals_.begin(); it != deals_.end(); ++it) {
                it->show();
            }
        }

        void showImportants() {
            int i = 1;
            for (auto it = importants_.begin(); it != importants_.end(); ++it) {
                std::cout << i << ". " << *it << std::endl;
                i++;
            }
        }

        void show() {
            std::cout << date_ << std::endl;
            showDeals();
            showImportants();
        }

        void edit(base_t* base) {
            std::string input;

            this->show();

            std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;

            std::cout << "Date: ";
            std::cin >> input;
            if (!input.empty()) {
                this->label_ = input;
                input.clear();
            }


            std::cout << "Deals: ";
            for (auto it = deals_.begin(); it != deals_.end(); ++it) {
                it->edit();
            }

            std::cout << "Importants: ";
            for (auto it = importants_.begin(); it != importants_.end(); ++it) {
                std::cin >> input;
                if (!input.empty()) {
                *it = input;
                input.clear();
            }
            
            std::cout << std::endl;

            base->update(*this);
        }        

        std::string concatenate() {
            std::string tmp;
            for (auto it = importants_.begin(); it != importants_.end(); ++it) {
                tmp += *it;
            }
            return date_                     +SEPARATOR+
                   std::to_string(uniqueId_) +SEPARATOR+
                   tmp;
        }

        void deconcatenate(const std::string& msg) {
            std::size_t counter = 0;
            std::size_t posBegin = 0;
            std::size_t numOfImportant = 0;

            for (std::size_t i = 0; i != msg.size(); ++i) {
                if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
                    if (counter == 0) {
                        counter++;
                        date_ = msg.substr(posBegin, i-1);
                        posBegin = i+SEPARATOR.size();
                    } else if (counter == 1) {
                        counter++;
                        uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                        posBegin = i+SEPARATOR.size();
                    } else if (counter > 1) {
                        addImportant(std::string(std::to_string(numOfImportant)+
                                     msg.substr(posBegin, i-1)));
                        posBegin = i+SEPARATOR.size();
                        numOfImportant++;
                    }
                }
            }
        }
        std::string date_;
        std::vector<Deal> deals_;
        std::vector<Important> importants_;
};

bool operator==(const Day& left, const Day& right) {
    return (left.getDate() == right.getDate())   &&
           (left.getDeals() == right.getDeals()) &&
           (left.getImportants() == right.getImportants()) &&
           (left.getVersion() == right.getVersion());
}
#endif // DAY_H
