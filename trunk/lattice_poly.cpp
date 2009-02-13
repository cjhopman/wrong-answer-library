/*
 * lattice_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include "lattice_prim.cpp"
#include <vector>
#include <algorithm>

typedef vector<pt> polygon;

/* Returns 2 * (area of polygon vv) */
//** NOT TESTED
double area_polygon(polygon &vv)
{
    double A = 0.0;
    vv.push_back(*vv.begin());

    for (int i = 1; i < vv.size(); i++)
        A += det(vv[i-1], vv[i]);

    vv.pop_back();
    return abs(A);
}

// vertices should be in counterclockwise order, with a0 == an
//** NOT TESTED
bool inside_convex(pt p, polygon& vv)
{
    vv.push_back(*vv.begin());
	for (unsigned i = 1; i < vv.size(); i++)
        if ( det(vv[i] - vv[i-1], p - vv[i-1]) < 0 )
            return false;
	return true;
}
/* Number of boundary points - points in vv MUST be on lattice! */
//** NOT TESTED
int boundary(polygon &vv)
{
    int c = 0;
    vv.push_back(*vv.begin());
    for (int i = 1; i < vv.size(); i++)
    {
        pt t = vv[i] - vv[i-1];
        c += abs(gcd( round(real(t)), round(imag(t)) ));
    }
    vv.pop_back();
    return c;
}

/*
 * Pick's theorem states A=I+B/2-1
 */

