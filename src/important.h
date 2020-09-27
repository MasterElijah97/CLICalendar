#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <string>

class Important : public IVersion, public IUniqueId, public IDatabase
{
public:
    important() = default;
    std::string important_;
    std::string getImportant() const;
    void setImportant(std::string);

};

#endif // IMPORTANT_H
