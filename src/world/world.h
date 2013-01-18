#ifndef WORLD_H
#define WORLD_H

#include <src/base/gamethread.h>

#include <mutex>
#include <condition_variable>

class World : public GameThread
{
public:
    World();
    virtual ~World();

    void operator ()();

private:
    void init();
    void deinit();

    bool inited;
    std::mutex mutex;
    std::condition_variable cond;
};

#endif // WORLD_H
