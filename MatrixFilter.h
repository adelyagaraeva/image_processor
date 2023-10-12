#pragma once
#include <vector>
#include "Image.h"
#include "AbstractFilter.h"

class MatrixFilter : virtual public AbstractFilter {
    std::vector<std::vector<int>> matrix_ = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

public:
    explicit MatrixFilter(const std::vector<std::vector<int>> matrix);
    void Apply(Image& copy) override;
    ~MatrixFilter() override = default;
};
