#include "gamethread.h"

GameThread::GameThread(unsigned int limit)
    : inited(false)
    , frameLimiter(limit)
{
}

unsigned int GameThread::fps()
{
    return frameCounter.fps();
}

unsigned int GameThread::time()
{
    return frameLimiter.duration();
}

void GameThread::beginTick()
{
    frameCounter.tick();
}

void GameThread::endTick()
{
    frameLimiter.tick();
}

void GameThread::setLimit(unsigned int limit)
{
    frameLimiter.setLimit(limit);
}

void GameThread::initNotify()
{
    inited = true;
    cond.notify_one();
}



void GameThread::waitForInit()
{
    if (inited) {
        return;
    }

    std::unique_lock<std::mutex> lock(mutex);

    while (!inited) {
        cond.wait(lock);
    }

    lock.unlock();
}
