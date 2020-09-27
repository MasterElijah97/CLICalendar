#ifndef IVERSION_H
#define IVERSION_H

#include "src/sqlite_orm.h"

class IVersion {

    public:
        IVersion() {
            this->version_ = 0;
        }

        std::size_t getVersion() const {
            return this->version_;
        }

        void updateVersion() {
            this->version_++;
        }

        std::size_t version_;
};

#endif // IVERSION_H
