
#include "Parser.h"
#include "Image.h"
#include "Controller.h"
#include "iostream"
#include "string_view"

void NoParams() {
    std::cout << "It's a simple image processor\n"
                 "Image format: 24-bit .bmp\n"
                 "Available filters:\n"
                 "Crop\n"
                 "Negative\n"
                 "Sharpening\n"
                 "Gray Scale\n"
                 "Edge Detection\n"
              << std::endl;
}
int main(int argc, char** argv) {
    if (argc == 1) {
        NoParams();
    } else {
        auto args = Parser::ParseArgs(argc, argv);
        Image copy(0, 0);
        try {
            copy.Read(static_cast<std::string>(args.input_path));
        } catch (OpenError& e) {
            std::cout << "Your file could not be open" << std::endl;
        } catch (WrongFileType& e) {
            std::cout << "Wrong file type" << std::endl;
        } catch (...) {
            std::cout << "Reading error" << std::endl;
        }
        Controller::ApplyFilters(args, copy);
        try {
            copy.Write(args.output_path);
        } catch (OpenError& e) {
            std::cout << "Your file could not be open" << std::endl;
        } catch (...) {
            std::cout << "Writing error" << std::endl;
        }
    }
    return 0;
}
