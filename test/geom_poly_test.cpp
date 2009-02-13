#include "../geom_poly.cpp"

#include <iostream>
#include <cassert>
#include <cmath>
#define ASSERT(x) assert((x))
#define approx(a, b) assert( abs(a-b) < EPS)
#define equal(a, b) assert( a == b )
#define ptinvalid(a) assert( isnan(imag(a)) || isnan(real(a)) || isinf(imag(a)) || isinf(real(a)) )


int main (int argc, char **argv)
{
    area_polygon_test();
    distPtSeg_test();
    xSegSeg_test();
    xLineLine_test();
    isParallel_test();
    xPtSeg_test();
    in_triangle_test();
    return 0;
}


