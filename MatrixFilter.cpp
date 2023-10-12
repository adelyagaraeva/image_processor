#include "MatrixFilter.h"
#include "utility"
#include "iostream"
MatrixFilter::MatrixFilter(const std::vector<std::vector<int>> matrix) {
    int size = 3;
    for (int y_m = 0; y_m < size; ++y_m) {
        for (int x_m = 0; x_m < size; ++x_m) {
            matrix_[x_m][y_m] = matrix[x_m][y_m];
        }
    }
};

void MatrixFilter::Apply(Image& copy) {
    Image temple = copy;
    for (int y = 0; y < copy.GetLength(); ++y) {
        for (int x = 0; x < copy.GetWidth(); ++x) {
            std::pair<int, int> left_up = {std::max(0, x - 1), std::max(0, y - 1)};
            std::pair<int, int> up = {x, std::max(0, y - 1)};
            std::pair<int, int> right_up = {std::min(copy.GetWidth() - 1, x + 1), std::max(0, y - 1)};
            std::pair<int, int> left = {std::max(0, x - 1), y};
            std::pair<int, int> right = {std::min(copy.GetWidth() - 1, x + 1), y};
            std::pair<int, int> left_down = {std::max(0, x - 1), std::min(copy.GetLength() - 1, y + 1)};
            std::pair<int, int> down = {x, std::min(copy.GetLength() - 1, y + 1)};
            std::pair<int, int> right_down = {std::min(copy.GetWidth() - 1, x + 1),
                                              std::min(copy.GetLength() - 1, y + 1)};
            std::vector<std::pair<int, int>> coord = {left_up, up,        right_up, left,      {x, y},
                                                      right,   left_down, down,     right_down};
            int size = 3;
            int counter = 0;
            float red = 0.0;
            float green = 0.0;
            float blue = 0.0;
            for (int y_m = 0; y_m < size; ++y_m) {
                for (int x_m = 0; x_m < size; ++x_m) {
                    Color pixel_color = temple.GetColor(coord[counter].first, coord[counter].second);
                    red += static_cast<float>(static_cast<float>(matrix_[x_m][y_m]) * pixel_color.r_);
                    green += static_cast<float>(static_cast<float>(matrix_[x_m][y_m]) * pixel_color.g_);
                    blue += static_cast<float>(static_cast<float>(matrix_[x_m][y_m]) * pixel_color.b_);
                    counter++;
                }
            }
            copy.SetColor(
                Color(std::min(static_cast<float>(1.0), std::max(static_cast<float>(0.0), static_cast<float>(red))),
                      std::min(static_cast<float>(1.0), std::max(static_cast<float>(0.0), static_cast<float>(blue))),
                      std::min(static_cast<float>(1.0), std::max(static_cast<float>(0.0), static_cast<float>(green)))),
                x, y);
        }
    }
};
