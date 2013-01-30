#include "prop.h"

Prop::Prop(const std::string &name)
    : Base(name)
{
}

Prop::Prop(const std::string &name, const Space &space)
    : Base(name, space)
{
}

Prop::~Prop()
{
}

