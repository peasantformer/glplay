#include "framelimiter.h"

#include <thread>
#include <iostream>

FrameLimiter::FrameLimiter(unsigned int limit)
    : microWait(1.0f/limit * 1000000.0f)
    , cycleDuration(0)
    , underflow(0)
{
    seconds = hr_clock_t::now();
}

FrameLimiter::~FrameLimiter()
{
}

void FrameLimiter::tick()
{
    time_point_t now = hr_clock_t::now();
    unsigned int dtm = std::chrono::duration_cast<std::chrono::microseconds>(now-seconds).count();

    cycleDuration = dtm;

    int waitTime = microWait - dtm - underflow;
    underflow = 0;
    if (waitTime <= 0) {
        underflow = waitTime * -1;
        //if (underflow > microWait) underflow = microWait;
        seconds = now;
        return;
    }


    std::this_thread::sleep_for(std::chrono::microseconds(waitTime));
    seconds = hr_clock_t::now();
}

void FrameLimiter::wait() const
{
    std::this_thread::sleep_for(std::chrono::microseconds(microWait));
}

unsigned int FrameLimiter::duration() const
{
    return cycleDuration;
}

void FrameLimiter::setLimit(unsigned int limit)
{
    microWait = 1.0f/limit * 1000000.0f;
}
