#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H

#include <chrono>

class FrameCounter
{
public:
    FrameCounter();
    virtual ~FrameCounter();

    void tick();
    unsigned int fps() const;
    unsigned int time() const;

private:
    typedef std::chrono::high_resolution_clock hr_clock_t;
    typedef std::chrono::time_point<hr_clock_t> time_point_t;
    time_point_t seconds;
    time_point_t starter;

    unsigned int frames;
    unsigned int frameRate;
};

#endif // FRAMECOUNTER_H
