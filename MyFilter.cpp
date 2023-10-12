#include "MyFilter.h"

void MyFilter::Apply(Image& copy) {
    for (int y = 0; y < copy.GetLength(); y++) {
        for (int x = 0; x < copy.GetWidth(); x++) {
            if (y % 3 != 0 && x % 3 != 0) {
                float color =
                    static_cast<float>((copy.GetColor(x, y).r_ + copy.GetColor(x, y).b_ + copy.GetColor(x, y).g_) / 3);
                color = 1 - color * static_cast<float>((x - copy.GetWidth()) / copy.GetWidth());
                copy.SetColor(Color(color, color, color), x, y);
            } else {
                const int scale = 10;
                const int max_size = 255;
                float div = static_cast<float>(std::abs((x - copy.GetWidth() / 2) / scale));
                float red = (copy.GetColor(x, y).r_ + copy.GetColor(x, y).b_ + copy.GetColor(x, y).g_);
                copy.SetColor(
                    Color(red + 1 - static_cast<float>(div / max_size), 1 - static_cast<float>(div / max_size), 0), x,
                    y);
            }
        }
    }
};
