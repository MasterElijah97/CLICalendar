#ifndef IUNIQUEID_H
#define IUNIQUEID_H

#include "src/sqlite_orm.h"

template<class... Ts>
class IUniqueId {
    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);

    public:
        IUniqueId() {
            uniqueId_ = 0;
        }

        std::size_t getUniqueId() const {
            return this->uniqueId_;
        }

        void setUniqueId(std::size_t id) {
            uniqueId_ = id;
        }

    protected:
        std::size_t uniqueId_;
};

#endif // IUNIQUEID_H
