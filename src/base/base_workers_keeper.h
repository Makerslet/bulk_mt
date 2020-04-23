#ifndef BASE_WORKERS_KEEPER_H
#define BASE_WORKERS_KEEPER_H

#include <functional>
#include <atomic>
#include <memory>
#include <condition_variable>
#include <queue>

using worker_task = std::function<void()>;

struct worker_context
{
    worker_context()
    {
        num_blocks.store(0);
        num_commands.store(0);
    }

    std::atomic<size_t> num_blocks;
    std::atomic<size_t> num_commands;
    const std::string name;
};

using context_sptr = std::shared_ptr<worker_context>;


class base_workers_keeper
{
public:
    virtual ~base_workers_keeper() = default;

    virtual size_t num_workers() const = 0;
    virtual context_sptr get_worker_context(size_t worker_index) = 0;
};

#endif // BASE_WORKERS_KEEPER_H
