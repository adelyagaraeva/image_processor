#pragma once
#include "Parser.h"
#include "Image.h"
#include "Negative.h"
#include "Crop.h"
#include "GrayScale.h"
#include "Sharpenning.h"
#include "AbstractFilter.h"
#include <memory>
#include <iostream>
#include "EdgeDet.h"
#include "MyFilter.h"
#include "Gaussian.h"

class Controller {
public:
    static void ApplyFilters(Parser::Args& args, Image& copy);
};
