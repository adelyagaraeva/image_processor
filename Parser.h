#pragma once

#include <vector>
#include <string>
#include <map>
class Parser {
public:
    struct Args {
        char* input_path;
        char* output_path;
        std::vector<std::string_view> filters;
        std::map<std::string_view, std::vector<std::string_view>> params;
    };

    static Args ParseArgs(int argc, char** argv);
};
