#ifndef IUNIQUEID_H
#define IUNIQUEID_H

#include "src/sqlite_orm.h"

class IUniqueId {

    public:
        IUniqueId() {
            uniqueId_ = 0;
        }

        int getId() const;
        void setId(std::size_t);

        int id_;
};

#endif // IUNIQUEID_H
