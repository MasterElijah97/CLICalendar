#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <string>

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

#endif // IMPORTANT_H
