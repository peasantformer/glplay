#ifndef SADEMOSQUARE_H
#define SADEMOSQUARE_H

#include <src/world/objects/worldobject.h>

class SadEmoSquare : public WorldObject
{
public:
    SadEmoSquare(std::string const& name, float width, float height, float depth);
    virtual ~SadEmoSquare();

protected:
    int width, height, depth;

    virtual void populateData(GLMeshSource & source);
};

#endif // SADEMOSQUARE_H
