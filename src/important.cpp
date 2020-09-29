#include "important.h"

Important::Important(const Important& other) {
	this->important_ = other.important_;
}
Important::Important(Important&& other) {
	this->important_ = other.important_;
}
Important& Important::operator=(const Important& other) {
	if (this == &other) {
        return *this;
    }
	this->important_ = other.important_;
	return *this;

}
Important& Important::operator=(Important&&) {
	if (this == &other) {
        return *this;
    }
	this->important_ = other.important_;
	return *this;
}

std::string Important::getImportant() const {
    	return this->important_;
}
void Impportant::setImportant(std::string msg) {
	this->important_ = std::move(msg);
	base_->insert(*this);
}
