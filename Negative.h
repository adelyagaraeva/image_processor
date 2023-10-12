#pragma once
#include "Image.h"
#include "AbstractFilter.h"

class Negative : virtual public AbstractFilter {
public:
    void Apply(Image& copy) override;
    ~Negative() override = default;
};
