#ifndef COMMANDS_QUEUE_H
#define COMMANDS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

/**
 * @brief Класс многопоточной неограниченной очереди,
 * обеспечивающей ожидание и уведомление читающих потоков
 */
template<typename T>
class queue_mt
{
public:
    /**
     * @brief Конструктор
     */
    queue_mt()
    {
        _running.store(true);
    }

    /**
     * @brief Положить элемен в очередь
     */
    void push(const T& value)
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        _cmds_queue.push(value);
        lock.unlock();
        _cond_var.notify_one();
    }

    /**
     * @brief Извлечь элемент из очереди
     */
    bool pop(T& value)
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        auto wait_lambda = [this](){return  !_cmds_queue.empty() || !_running.load();};
        _cond_var.wait(lock, wait_lambda);

        if(_cmds_queue.empty())
            return false;
        else
        {
            value = _cmds_queue.front();
            _cmds_queue.pop();
            return true;
        }
    }

    /**
     * @brief Остановить работу очереди
     */
    void shutdown()
    {
        _running.store(false);
        _cond_var.notify_all();
    }

    /**
     * @brief Проверить запущена ли очередь
     */
    bool is_running()
    {
        return _running.load();
    }

private:
    std::condition_variable _cond_var;
    std::mutex _control_mutex;
    std::queue<T> _cmds_queue;
    std::atomic<bool> _running;
};

#endif // COMMANDS_QUEUE_H
