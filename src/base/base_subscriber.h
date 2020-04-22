#ifndef BASE_SUBSCRIBER_H
#define BASE_SUBSCRIBER_H

#include <vector>
#include <string>
#include <memory>

/**
 * @brief Описание задачи для вывода
 */
struct task {
    task(uint64_t ts, const std::vector<std::string>& cmds) :
        timestamp(ts), commands(cmds){}

    const uint64_t timestamp;
    const std::vector<std::string> commands;
};

/**
 * @brief Интерфейс подписчика
 */
struct base_subscriber {
    using task_sptr = std::shared_ptr<task>;
    /**
     * @brief Деструктор подписчика
     */
    virtual ~base_subscriber() = default;
    /**
     * @brief Интерфейс получения уведомлений
     * @timestamp - временная метка
     * @str - информационная строка
     */
    virtual void update(task_sptr) = 0;
};

#endif // BASE_SUBSCRIBER_H
