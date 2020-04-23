#ifndef SUBSCRIBER_HANDLER_CREATOR_H
#define SUBSCRIBER_HANDLER_CREATOR_H

#include "base/base_subscriber.h"

class subscriber_handler_creator
{
public:
    static subscriber_task_handler create_console_handler();
    static subscriber_task_handler create_file_handler();
};

#endif // SUBSCRIBER_HANDLER_CREATOR_H
