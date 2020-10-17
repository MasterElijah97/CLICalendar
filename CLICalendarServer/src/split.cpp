#include <split.h>

std::vector<std::string> split(const std::string& input, char separator) {

    std::vector<std::string> args;

    std::istringstream input_ss {input};

    for (std::string arg; std::getline(input_ss, arg, separator); ) {
        args.push_back(arg);
    }

    return args;
}
