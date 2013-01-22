#ifndef WORLDACTION_H
#define WORLDACTION_H

class World;

class WorldAction
{
public:
    WorldAction();
    virtual ~WorldAction();
    virtual void visit(World & world) = 0;
};

#endif // WORLDACTION_H
