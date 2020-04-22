#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <optional>

namespace bpo = boost::program_options;

class args_parser
{
public:
    args_parser();
    std::optional<size_t> parse(int argc, char**argv);

private:
    bpo::options_description _description;
    bpo::variables_map _values_storage;
};

#endif // ARGS_PARSER_H