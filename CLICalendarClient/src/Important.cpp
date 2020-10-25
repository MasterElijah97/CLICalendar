#include "Important.h"

bool operator==(const Important& left, const Important& right) {
    return left.important_ == right.important_;
}

void Important::updateVersion() {
    this->version_++;
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
}
Important::Important(Important&& other) {
	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;
}
Important& Important::operator=(const Important& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;

	return *this;

}
Important& Important::operator=(Important&& other) {
	if (this == &other) {
        return *this;
    }

	this->important_ = other.important_;
	this->id_        = other.id_;
	this->version_   = other.version_;

	return *this;
}

void Important::show() {
    std::cout << std::setw(13) << important_ << std::endl;
}
void Important::edit() {
    std::string input;

    this->show();

    std::cout << "Please, enter new information or click enter to remain old data: " << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(13) << "Important: " << std::endl;
    std::getline(std::cin, input, '\n');
    std::cout << std::endl;
    if (input.size() > 1) {
        this->important_ = input;
        input.clear();
    }

    this->updateVersion();
}

void Important::setImportant(std::string msg) {
	this->important_ = std::move(msg);
}
void Important::setDate(std::string date) {
    this->date_ = std::move(date);
}

