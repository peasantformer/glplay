#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <src/base/thread.h>
#include <src/util/framecounter.h>
#include <src/util/framelimiter.h>

#include <mutex>
#include <condition_variable>

class GameThread : public Thread
{
public:
    GameThread(unsigned int limit = 60);
    unsigned int fps();
    unsigned int time();
    void waitForInit();

protected:
    void beginTick();
    void endTick();
    void setLimit(unsigned int);
    void initNotify();

private:
    FrameCounter frameCounter;
    FrameLimiter frameLimiter;

    bool inited;
    std::mutex mutex;
    std::condition_variable cond;
};

#endif // GAMETHREAD_H
