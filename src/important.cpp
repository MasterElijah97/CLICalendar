#include "important.h"

std::string Important::getImportant() const {
    	return this->important_;
}

void Impportant::setImportant(std::string msg) {
	this->important_ = std::move(msg);
}
