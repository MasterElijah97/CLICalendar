#ifndef IVERSION_H
#define IVERSION_H

#include "include/sqlite_orm.h"

#include "src/black_magic.h"

class IVersion {

    public:
        IVersion();
        std::size_t getVersion() const {
            return this->version_;
        }

        void setVersion(std::size_t);

        void updateVersion();

        std::size_t version_;
};

#endif // IVERSION_H
