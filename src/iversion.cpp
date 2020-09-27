#include "iversion.h"

IVersion::IVersion()
{
	this->version_ = 0;
}

std::size_t IVersion::getVersion() const {
    return this->version_;
}

void IVersion::setVersion(std::size_t ver) {
	this->version_ = std::move(ver);
}

void IVersion::updateVersion() {
	this->version_++;
}