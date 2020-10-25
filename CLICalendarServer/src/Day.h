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
