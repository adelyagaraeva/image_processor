project(image_processor)

add_executable(
        image_processor
        image_processor.cpp
        Parser.cpp Image.cpp Controller.cpp Negative.cpp Crop.cpp GrayScale.cpp Sharpenning.cpp EdgeDet.cpp MatrixFilter.cpp MyFilter.cpp Gaussian.cpp unit_tests/test.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fsanitize=address")

add_subdirectory(unit_tests)
