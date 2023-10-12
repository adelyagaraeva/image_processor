#pragma once
#include "Image.h"
#include "AbstractFilter.h"
class Crop : virtual public AbstractFilter {
    int width_ = 0;
    int length_ = 0;

public:
    explicit Crop(int width, int length);
    void Apply(Image& copy) override;
    ~Crop() override = default;
};
