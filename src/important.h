#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <string>

#include "include/sqlite_orm.h"

#include "src/black_magic.h"

#include "src/iversion.h"
#include "src/iuniqueid.h"
#include "src/idatabase.h"

class Important : public IVersion, public IUniqueId, public IDatabase
{
public:
    Important() = default;
    Important(const Important&);
    Important(Important&&);
    Important& operator=(const Important&);
    Important& operator=(Important&&);

    std::string important_;
    
    std::string getImportant() const;
    void setImportant(std::string);

};

bool operator==(const Important& left, const Important& right) {
    return left.important_ == right.important_;
}

#endif // IMPORTANT_H
