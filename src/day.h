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
#include "src/deal.h"
#include "src/important.h"

const std::string SEPARATOR(3, '&');

class Day : public IVersion, public IUniqueId, public IDatabase {

    public:
        Day();
        Day(std::string);
        Day(const Day&);
        Day(Day&&);
        Day& operator=(const Day&);
        Day& operator=(Day&&);

        ~Day() = default;

        friend bool operator==(const Day& left, const Day& right);

        std::string getDate() const;
        std::vector<Deal> getDeals() const;
        std::vector<Impportant> getImportants() const;

        void setDate(std::string);

        void addDeal(Deal);
        void addImportant(std::string);

        //todo -------------
        void removeDeal(int);
        void editDeal(int);

        void removeImportant(int);
        void editImportant(int);
        //------------------
        //funcs
        void showDeals();
        void showImportants();
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        std::string date_;
        std::vector<Deal> deals_;
        std::vector<Important> importants_;
};

bool operator==(const Day& left, const Day& right) {
    return (left.date_ == right.date_)   &&
           (left.deals_ == right.deals_) &&
           (left.importants_ == right.importants) &&
           (left.version_ == right.version_);
}
#endif // DAY_H
