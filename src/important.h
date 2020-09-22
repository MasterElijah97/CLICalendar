#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <string>

class Important : public IVersion, public IUniqueId
{
public:
    important();
    std::string important_;
};

#endif // IMPORTANT_H
