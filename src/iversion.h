#ifndef IVERSION_H
#define IVERSION_H

#include "src/sqlite_orm.h"

template<class... Ts>
class IVersion {

    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);
    public:
        IVersion() : version_(0) {

        }

        std::size_t getVersion() const {
            return this->version_;
        }

        void updateVersion() {
            this->version_++;
        }

    protected:
        std::size_t version_;
};

#endif // IVERSION_H
