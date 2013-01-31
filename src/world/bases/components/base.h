#ifndef BASE_H
#define BASE_H

#include <src/world/space.h>

#include <string>

class Base
{
public:
    Base(std::string const& name);
    Base(std::string const& name, Space const& space);
    virtual ~Base();

    Space space;
    std::string name;
};

#endif // BASE_H
