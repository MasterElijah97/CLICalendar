#ifndef IDATABASE_H
#define IDATABASE_H

#include "black_magic.h"

class IDatabase
{
public:
    IDatabase() = default;
    base_t* base_;
    void addBasePtr(base_t*);
};

#endif // IDATABASE_H
