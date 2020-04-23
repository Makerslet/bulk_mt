#ifndef STATISTIC_FORMATTER_H
#define STATISTIC_FORMATTER_H

#include "base/base_workers_keeper.h"
#include "command_handler.h"

class statistic_formatter
{
public:
    static std::string format(const std::string& thread_name,
                      context_sptr stat);
    static std::string format(const command_handler_statistic& stat);
};

#endif // STATISTIC_FORMATTER_H
