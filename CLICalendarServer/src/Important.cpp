#include "Important.h"

bool operator==(const Important& left, const Important& right) {
    return left.important_ == right.important_;
}

Important::Important() {
    this->id_      = -1;
    this->version_ = 1;
}
Important::Important(std::string important) {
    this->important_ = important;
    this->id_        = -1;
    this->version_   = 1;
}
Important::Important(const Important& other) {
	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
	this->date_      = other.date_;
}
Important::Important(Important&& other) {
	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
	this->date_      = other.date_;
}
Important& Important::operator=(const Important& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
	this->date_      = other.date_;

	return *this;

}
Important& Important::operator=(Important&& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
	this->date_      = other.date_;

	return *this;
}