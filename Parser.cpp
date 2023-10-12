#include "Parser.h"
#include "iostream"

Parser::Args Parser::ParseArgs(int argc, char** argv) {
    Args res;
    bool is_input = false;
    bool is_output = false;
    std::string_view filter;
    for (int j = 1; j < argc; ++j) {
        if (!is_input) {
            res.input_path = argv[j];
            is_input = true;
        } else if (!is_output) {
            res.output_path = argv[j];
            is_output = true;
        } else {
            if (static_cast<std::string_view>(argv[j]).front() == '-') {
                filter = static_cast<std::string_view>(argv[j]);
                res.filters.push_back(filter);
            } else {
                res.params[filter].push_back(static_cast<std::string_view>(argv[j]));
            }
        }
    }

    return res;
};
