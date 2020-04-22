#include "args_parser.h"

#include <iostream>

args_parser::args_parser() :
    _description("allowed options")
{
    _description.add_options()
            ("help", "Type exit for exit")
            ("length", boost::program_options::value<size_t>(), "set bulk length");
}

std::optional<size_t> args_parser::parse(int argc, char **argv)
{
    std::optional<size_t> return_value;
    auto parsed_options = boost::program_options::parse_command_line(argc, argv, _description);
    boost::program_options::store(parsed_options, _values_storage);


    if(_values_storage.count("help")) {
        std::cout << _description << std::endl;
        return return_value;
    }

    if(!_values_storage.count("length"))
        std::cout << "bulk length wasn't set, can't continue, exiting..." << std::endl;
    else
    {
        std::size_t tmp = _values_storage["length"].as<size_t>();
        if(tmp > 0)
            return_value = tmp;
        else
            std::cout << "bulk length can't be 0, exiting..." << std::endl;
    }

    return return_value;
}
