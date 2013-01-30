#include "base.h"

Base::Base(const std::string &name)
    : name(name)
{
}

Base::Base(const std::string &name, const Space &space)
    : name(name)
    , space(space)
{
}

Base::~Base()
{
}

