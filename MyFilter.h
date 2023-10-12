#pragma once
#include "Image.h"
#include "AbstractFilter.h"
#include "Sharpenning.h"

class MyFilter : virtual public AbstractFilter {
public:
    void Apply(Image& copy) override;
    ~MyFilter() override = default;
};
