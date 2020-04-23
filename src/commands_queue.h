#ifndef COMMANDS_QUEUE_H
#define COMMANDS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class queue_mt
{
public:
    queue_mt()
    {}

    void push(const T& request)
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        _cmds_queue.push(request);
        lock.unlock();
        _cond_var.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        _cond_var.wait(lock, [this](){return !_cmds_queue.empty();});

        T value = _cmds_queue.front();
        _cmds_queue.pop();

        return value;
    }

private:
    std::condition_variable _cond_var;
    std::mutex _control_mutex;
    std::queue<T> _cmds_queue;
};

#endif // COMMANDS_QUEUE_H
