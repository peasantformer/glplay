#ifndef THREAD_H
#define THREAD_H

class Thread
{
public:
    Thread();
    virtual ~Thread();

    virtual void operator()() = 0;
    virtual void stop();
    virtual bool isDone() const;

protected:
    volatile bool done;

};

#endif // THREAD_H
