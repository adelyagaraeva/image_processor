#pragma once
#include "Image.h"
#include "AbstractFilter.h"
#include "GrayScale.h"
#include "MatrixFilter.h"

class EdgeDet : public MatrixFilter, public GrayScale {
    float treshold_ = 0.0;

public:
    explicit EdgeDet(float treshold);
    void Apply(Image& copy) override;
    ~EdgeDet() override = default;
};
