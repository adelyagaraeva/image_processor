#include "GrayScale.h"

void GrayScale::Apply(Image& copy) {
    for (int y = 0; y < copy.GetLength(); ++y) {
        for (int x = 0; x < copy.GetWidth(); ++x) {
            float color = RED_COEFF * copy.GetColor(x, y).r_ + BLUE_COEFF * copy.GetColor(x, y).b_ +
                          GREEN_COEFF * copy.GetColor(x, y).g_;
            copy.SetColor(Color(color, color, color), x, y);
        }
    }
};
