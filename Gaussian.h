#pragma once

#include "Image.h"
#include "AbstractFilter.h"

class Gaussian : public AbstractFilter {
public:
    explicit Gaussian(double sigma);
    void Apply(Image& copy) override;
    ~Gaussian() override = default;

private:
    std::vector<float> coeffs_;
};
