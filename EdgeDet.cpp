#include "EdgeDet.h"

EdgeDet::EdgeDet(float treashold) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), treshold_(treashold){};

void EdgeDet::Apply(Image& copy) {
    GrayScale::Apply(copy);
    MatrixFilter::Apply(copy);
    for (int y = 0; y < copy.GetLength(); ++y) {
        for (int x = 0; x < copy.GetWidth(); ++x) {
            if (copy.GetColor(x, y).r_ > treshold_) {
                copy.SetColor(Color(1.0, 1.0, 1.0), x, y);
            } else {
                copy.SetColor(Color(0.0, 0.0, 0.0), x, y);
            }
        }
    }
};
