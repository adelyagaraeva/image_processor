#include "Negative.h"

void Negative::Apply(Image& copy) {
    for (int y = 0; y < copy.GetLength(); ++y) {
        for (int x = 0; x < copy.GetWidth(); ++x) {
            copy.SetColor(Color(1 - copy.GetColor(x, y).r_, 1 - copy.GetColor(x, y).b_, 1 - copy.GetColor(x, y).g_), x,
                          y);
        }
    }
};
