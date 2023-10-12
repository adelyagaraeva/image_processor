#include "Crop.h"
#include "iterator"
#include "iostream"
Crop::Crop(int width, int length) : width_(width), length_(length){};

void Crop::Apply(Image& copy) {
    if (length_ < copy.GetLength()) {
        auto iterator1 = copy.GetData().begin();
        auto iterator2 = iterator1 + copy.GetWidth() - length_;
        copy.GetData().erase(iterator1, iterator2);
        copy.SetLength(length_);
    }
    if (width_ < copy.GetWidth()) {
        for (int y = 0; y < copy.GetLength(); ++y) {
            auto iterator_1 = copy.GetData()[y].end();
            auto iterator_2 = iterator_1 - (copy.GetWidth() - width_);
            copy.GetData()[y].erase(iterator_2, iterator_1);
        }
        copy.SetWidth(width_);
    }
};
