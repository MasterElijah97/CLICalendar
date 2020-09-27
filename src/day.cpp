#include "day.h"

Day::Day()
{
	date_ = "01 January 1970";
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

Day::Day(const std::string date) {
    date_ = date;
    importants_.emplace_back("Nothing");
    deals_.emplace_back("Frist of All");
}

std::string Day::getDate() const {
    return date_;
}

std::vector<Deal> Day::getDeals() const {
    return deals_;
}

std::vector<Impportant> Day::getImportants() const {
    return importants_;
}