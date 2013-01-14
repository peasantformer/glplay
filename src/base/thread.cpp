#include "thread.h"

Thread::Thread()
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
