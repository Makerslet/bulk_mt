#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

struct util
{
    using commands = std::vector<std::string>;
    static std::string prepare_string_command(const commands& cmmds);
};

#endif // UTIL_H
