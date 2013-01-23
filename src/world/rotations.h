#ifndef ROTATIONS_H
#define ROTATIONS_H

class Rotations
{
public:
    Rotations();
    float pitch;
    float roll;
    float yaw;

    void shift(Rotations const& rhs);
};

#endif // ROTATIONS_H
