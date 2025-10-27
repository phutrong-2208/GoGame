#ifndef MATH_FUNCTIONS_HPP
#define MATH_FUNCTIONS_HPP

#include <math.h>

namespace mathFunctions{
    double Euclidean(double x1, double y1, double x2, double y2){ //Euclidean distance between two points
        x1 -= x2; y1 -= y2;
        return std :: sqrtl(x1 * x1 + y1 * y1);
    }
}
#endif MATH_FUNCTIONS_HPP
