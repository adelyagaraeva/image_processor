#include "Sharpenning.h"
const int CENTRAL_VALUE = 5;
Sharpenning::Sharpenning() : MatrixFilter({{0, -1, 0}, {-1, CENTRAL_VALUE, -1}, {0, -1, 0}}){};

void Sharpenning::Apply(Image& copy) {
    MatrixFilter::Apply(copy);
};
