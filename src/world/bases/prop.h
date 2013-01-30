#ifndef PROP_H
#define PROP_H

#include <src/world/bases/components/base.h>
#include <src/world/bases/components/physical.h>
#include <src/world/bases/components/renderable.h>
#include <src/world/bases/components/animatable.h>

class Prop : public Base, public Physical, public Renderable, public Animatable
{
public:
    Prop(std::string const& name);
    Prop(std::string const& name, Space const& space);
    virtual ~Prop();
};

#endif // PROP_H

