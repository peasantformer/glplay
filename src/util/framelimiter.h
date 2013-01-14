#ifndef FRAMELIMITER_H
#define FRAMELIMITER_H

#include <chrono>
#include <string>

class FrameLimiter
{
public:
    explicit FrameLimiter(unsigned int limit = 60);
    virtual ~FrameLimiter();

    void tick();
    void wait() const;
    unsigned int duration() const;
    void setLimit(unsigned int limit);

private:
    typedef std::chrono::high_resolution_clock hr_clock_t;
    typedef std::chrono::time_point<hr_clock_t> time_point_t;

    time_point_t seconds;
    unsigned int microWait;
    unsigned int cycleDuration;
    unsigned int underflow;
};

#endif // FRAMELIMITER_H
