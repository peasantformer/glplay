#include "framecounter.h"

FrameCounter::FrameCounter()
{
    seconds = hr_clock_t::now();
    starter = hr_clock_t::now();
    frameRate = 0;
    frames = 0;
}

FrameCounter::~FrameCounter()
{

}

void FrameCounter::tick()
{
    frames++;
    time_point_t now = hr_clock_t::now();
    unsigned int dts = std::chrono::duration_cast<std::chrono::microseconds>(now-seconds).count();

    if (dts > 1000000) {
        frameRate = frames;
        seconds = now;
        frames = 0;
    }
}

unsigned int FrameCounter::fps() const
{
    return frameRate;
}

unsigned int FrameCounter::time() const
{
    time_point_t now = hr_clock_t::now();
    unsigned int dts = std::chrono::duration_cast<std::chrono::microseconds>(now-seconds).count();

    return dts/1000;
}
