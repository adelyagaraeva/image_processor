#pragma once
#include "Image.h"
#include "AbstractFilter.h"
const float RED_COEFF = 0.299;
const float GREEN_COEFF = 0.587;
const float BLUE_COEFF = 0.114;

class GrayScale : virtual public AbstractFilter {
public:
    void Apply(Image& copy) override;
    ~GrayScale() override = default;
};
