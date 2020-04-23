#include "commands_factory.h"
#include "command_handler.h"
#include "subscriber.h"
#include "args_parser.h"
#include "subscriber_handler_creator.h"
#include "statistic_formatter.h"

#include <iostream>

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main (int argc, char** argv)
{
    args_parser parser;
    std::optional<size_t> result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;


    commands_factory cmd_factory;
    command_type cmd_type;
    command_handler cmd_handler(result.value());

    auto console_out_subscriber = std::make_shared<subscriber>(1,
            subscriber_handler_creator::create_console_handler());
    auto file_out_subscriber = std::make_shared<subscriber>(2,
            subscriber_handler_creator::create_file_handler());

    cmd_handler.subscribe(console_out_subscriber);
    cmd_handler.subscribe(file_out_subscriber);

    std::string argument;
    do {
        std::getline(std::cin, argument);
        auto command = cmd_factory.create_command(argument);
        cmd_type = command->type();
        cmd_handler.add_command(std::move(command));

    } while(cmd_type != command_type::finish);

    std::cout << statistic_formatter::format(cmd_handler.statistic()) << std::endl;
    std::cout << statistic_formatter::format("console thread",
            console_out_subscriber->get_worker_context(0)) << std::endl;
    std::cout << statistic_formatter::format("file thread 1",
            file_out_subscriber->get_worker_context(0)) << std::endl;
    std::cout << statistic_formatter::format("file thread 2",
            file_out_subscriber->get_worker_context(1)) << std::endl;
    return 0;
}


