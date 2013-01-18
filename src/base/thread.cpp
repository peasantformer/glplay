#include "thread.h"

Thread::Thread()
    : done(false)
{

}

Thread::~Thread()
{

}

void Thread::stop()
{
    done = true;
}

bool Thread::isDone() const
{
    return done;
}
