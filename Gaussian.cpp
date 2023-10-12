#include "Gaussian.h"
#include <cmath>

const int VL = 6;
const int VL2 = 2;
Gaussian::Gaussian(double sigma) {
    float pi = static_cast<float>(acos(-1.0));
    size_t size = static_cast<size_t>(std::ceil(VL * std::abs(sigma))) + VL2;
    if (size % 2 == 0) {
        size += 1;
    }
    coeffs_.resize(size);
    for (int delta = 0; delta <= static_cast<int>(size / 2); delta++) {
        float value = static_cast<float>(sqrt(1 / (2 * pi * sigma * sigma)) *
                                         std::exp((static_cast<float>(-delta * delta)) / (2 * sigma * sigma)));
        coeffs_[static_cast<int>(size / 2) - delta] = value;
        coeffs_[static_cast<int>(size / 2) + delta] = value;
    }
}

void Gaussian::Apply(Image& image) {
    std::vector<std::vector<Color>> vertical =
        std::vector<std::vector<Color>>(image.GetLength(), std::vector<Color>(image.GetWidth()));
    for (int x = 0; x < image.GetWidth(); ++x) {
        for (int y = 0; y < image.GetLength(); ++y) {
            Color pixel(0, 0, 0);
            for (int delta_y = -static_cast<int>(coeffs_.size() / 2); delta_y <= static_cast<int>(coeffs_.size() / 2);
                 ++delta_y) {
                int y0 = y + delta_y;
                if (y + delta_y < 0) {
                    y0 = 0;
                } else if (y + delta_y >= image.GetLength()) {
                    y0 = image.GetLength() - 1;
                }
                pixel.r_ += image.GetColor(x, y0).r_ * coeffs_[delta_y + static_cast<int>(coeffs_.size() / 2)];
                pixel.g_ += image.GetColor(x, y0).g_ * coeffs_[delta_y + static_cast<int>(coeffs_.size() / 2)];
                pixel.b_ += image.GetColor(x, y0).b_ * coeffs_[delta_y + static_cast<int>(coeffs_.size() / 2)];
            }
            vertical[x][y] = pixel;
        }
    }

    for (int y = 0; y < image.GetLength(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color pixel(0, 0, 0);
            for (int delta_x = -static_cast<int>(coeffs_.size() / 2); delta_x <= static_cast<int>(coeffs_.size() / 2);
                 delta_x++) {
                int x0 = x + delta_x;
                if (x + delta_x < 0) {
                    x0 = 0;
                } else if (x + delta_x >= image.GetWidth()) {
                    x0 = image.GetWidth() - 1;
                }
                pixel.r_ += vertical[x0][y].r_ * coeffs_[delta_x + static_cast<int>(coeffs_.size() / 2)];
                pixel.g_ += vertical[x0][y].g_ * coeffs_[delta_x + static_cast<int>(coeffs_.size() / 2)];
                pixel.b_ += vertical[x0][y].b_ * coeffs_[delta_x + static_cast<int>(coeffs_.size() / 2)];
            }
            image.SetColor(pixel, x, y);
        }
    }
}
