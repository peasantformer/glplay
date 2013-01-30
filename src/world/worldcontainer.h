#ifndef WORLDCONTAINER_H
#define WORLDCONTAINER_H

#include <src/util/blockingqueue.h>

#include <map>
#include <string>
#include <memory>

template <class T>
class WorldContainer
{
public:
    typedef typename std::map<std::string, std::shared_ptr<T> >::iterator iterator;
    typedef typename std::map<std::string, std::shared_ptr<T> >::const_iterator const_iterator;

    iterator begin() {
        return objects.begin();
    }

    iterator end() {
        return objects.end();
    }

    const_iterator begin() const {
        return objects.begin();
    }
    const_iterator end() const {
        return objects.end();
    }

    BlockingQueue<std::shared_ptr<T> > newObjects;
    std::map<std::string, std::shared_ptr<T> > objects;
};

#endif // WORLDCONTAINER_H
