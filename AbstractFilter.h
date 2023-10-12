#pragma once
#include "Image.h"

class AbstractFilter {
public:
    virtual void Apply(Image& img) = 0;
    virtual ~AbstractFilter() = default;
};
