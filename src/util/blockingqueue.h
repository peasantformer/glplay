#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue
{
public:
    BlockingQueue(unsigned int limit = 0)
        : limit(limit)
    {

    }

    void try_push(T const& el) {
        std::unique_lock<std::mutex> lock(mutex);
        if (full()) {
            lock.unlock();
            return;
        }
        data.push(el);
        lock.unlock();
        popCond.notify_one();
    }

    void wait_and_push(T const& el) {
        std::unique_lock<std::mutex> lock(mutex);
        if (full()) {
            pushCond.wait(lock);
        }
        data.push(el);
        lock.unlock();
        popCond.notify_one();
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mutex);
        bool result = data.empty();
        lock.unlock();
        return result;
    }

    bool full() {
        return limit > 0 && data.size() >= limit;
    }

    bool try_pop(T & el) {
        std::unique_lock<std::mutex> lock(mutex);

        if (data.empty()) {
            lock.unlock();
            return false;
        }

        el = data.front();
        data.pop();
        pushCond.notify_one();
        lock.unlock();
        return true;
    }

    void wait_and_pop(T & el) {
        std::unique_lock<std::mutex> lock(mutex);

        while (data.empty()) {
            popCond.wait(lock);
        }

        el = data.front();
        data.pop();
        pushCond.notify_one();
        lock.unlock();
    }

private:
    unsigned
    int limit;
    std::queue<T> data;
    std::mutex mutex;
    std::condition_variable popCond;
    std::condition_variable pushCond;
};

#endif // BLOCKINGQUEUE_H
