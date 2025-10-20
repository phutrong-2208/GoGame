#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <vector>

namespace mathFunctions{
    double Euclidean(double x1, double y1, double x2, double y2){ //Euclidean distance between two points
        x1 -= x2; y1 -= y2;
        return sqrtl(x1 * x1 + y1 * y1);
    }
}