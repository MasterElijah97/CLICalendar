#ifndef DAY_H
#define DAY_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "SEPARATOR.h"
#include "split.h"
#include "Deal.h"
#include "Important.h"

class Day {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;
        void updateVersion();

        Day();
        Day(std::string);
        Day(const Day&);
        Day(Day&&);

        //operators
        friend bool operator==(const Day& left, const Day& right);
        Day& operator=(const Day&);
        Day& operator=(Day&&);

        //destructor
        ~Day() = default;

        //setters
        void setDate(const std::string&);
        void addDeal(const Deal&);
        void addImportant(const Important&);

        //user's interface
        void removeDeal(std::size_t&);
        void editDeal(std::size_t&);

        void removeImportant(std::size_t&);
        void editImportant(std::size_t&);

        void showDeals();
        void showImportants();

        void show();
        void edit();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string);

        //members
        std::string date_;
        std::vector<Deal> deals_;           //#include <Deal.h>
        std::vector<Important> importants_; //#include <Impportant.h>
};

bool operator==(const Day&, const Day&);

#endif // DAY_H
