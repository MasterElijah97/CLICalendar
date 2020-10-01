#ifndef IUNIQUEID_H
#define IUNIQUEID_H

#include "include/sqlite_orm.h"

#include "src/black_magic.h"

class IUniqueId {

    public:
        IUniqueId() {
            id_ = 0;
        }

        int getId() const;
        void setId(std::size_t);

        int id_;
};

#endif // IUNIQUEID_H
