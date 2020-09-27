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

class Day : public IVersion, public IUniqueId, public IDatabase {

    public:
        Day();
        Day(const std::string);

        ~Day() = default;

        friend bool operator==(const Day& left, const Day& right);

        std::string getDate() const;
        std::vector<Deal> getDeals() const;
        std::vector<Impportant> getImportants() const;

        void setDate(std::string);

        void addDeal(Deal);
        void addImportant(std::string);

        //todo -------------
        void removeDeal(int, base_t*);
        void editDeal(int, base_t*);

        void removeImportant(int, base_t*);
        void editImportant(int, base_t*);
        //------------------
        //funcs
        void showDeals();
        void showImportants();
        void show();

        void edit(base_t*);

        std::string concatenate();
        void deconcatenate(const std::string&);

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
