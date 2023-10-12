#pragma once
#include <vector>
#include "Image.h"
#include "MatrixFilter.h"

class Sharpenning : public MatrixFilter {
public:
    explicit Sharpenning();
    void Apply(Image& copy) override;
    ~Sharpenning() override = default;
};
