#include "Controller.h"

void Controller::ApplyFilters(Parser::Args& args, Image& copy) {
    std::vector<std::shared_ptr<AbstractFilter>> filters;
    for (size_t i = 0; i < args.filters.size(); ++i) {
        if (args.filters[i] == "-neg") {
            filters.push_back(std::shared_ptr<AbstractFilter>(new Negative()));
        }
        if (args.filters[i] == "-crop") {
            int width = 0;
            int length = 0;
            width = std::stoi(static_cast<std::string>(args.params["-crop"][0]));
            length = std::stoi(static_cast<std::string>(args.params["-crop"][1]));
            filters.push_back(std::shared_ptr<AbstractFilter>(new Crop(width, length)));
        }
        if (args.filters[i] == "-gs") {
            filters.push_back(std::shared_ptr<AbstractFilter>(new GrayScale()));
        }
        if (args.filters[i] == "-sharp") {
            filters.push_back(std::shared_ptr<AbstractFilter>(new Sharpenning()));
        }
        if (args.filters[i] == "-edge") {
            std::string value = static_cast<std::string>(args.params["-edge"][0]);
            filters.push_back(std::shared_ptr<AbstractFilter>(new EdgeDet(stof(value))));
        }
        if (args.filters[i] == "-myf") {
            filters.push_back(std::shared_ptr<AbstractFilter>(new MyFilter()));
        }
        if (args.filters[i] == "-blur") {
            float val = std::stof(static_cast<std::string>(args.params["-blur"][0]));
            filters.push_back(std::shared_ptr<AbstractFilter>(new Gaussian(val)));
        }
    }
    for (auto const& filter_ptr : filters) {
        filter_ptr->Apply(copy);
    }
}
