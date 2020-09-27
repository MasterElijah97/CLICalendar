#include "iuniqueid.h"

IUniqueId::IUniqueId()
{
	this->id_ = -1;
}

int IUniqueId::getId() const {
    return this->id_;
}

void IUniqueId::setId(std::size_t id) {
    this->id_ = std::move(id);
}