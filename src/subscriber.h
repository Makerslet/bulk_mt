#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "commands_queue.h"

#include "base/base_subscriber.h"
#include "base/base_workers_keeper.h"

#include <thread>

/**
 * @brief Класс производящий вывод полученной команды в файл
 */
class subscriber : public base_subscriber, public base_workers_keeper
{
    using context_thread_pair = std::pair<context_sptr, std::thread>;
    using queue_sptr = std::shared_ptr<queue_mt<task_sptr>>;

public:
    /**
     * @brief Конструктор
     */
    subscriber(size_t num_workers, subscriber_task_handler subscriber_task);
    /**
     * @brief Обработка команды от publisher'а
     * @param timestamp - временная метка
     * @param out - текст
     */
    void update(task_sptr cmds) override;

    size_t num_workers() const override;
    context_sptr get_worker_context(size_t worker_index) override;

private:
    /**
     * @brief Метод записи в файл
     * @param timestamp - временная метка
     * @param out - текст
     */
    worker_task create_worker_handler(context_sptr context, queue_sptr queue_mt,
                                   subscriber_task_handler subscriber_task);
    void write(uint64_t timestamp, const std::string &out);

private:
    size_t _num_workers;
    queue_sptr _cmds_queue;
    std::vector<context_thread_pair> _workers;
};

#endif // SUBSCRIBER_H
