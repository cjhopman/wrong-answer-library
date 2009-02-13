/*
 * geom_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include "geom_prim.cpp"
#include <vector>
#include <algorithm>

typedef vector<pt> polygon;

//** NOT TESTED
int gcd(int a, int b)
{
    while (b != 0)
    { int t=b; b = a%b; a=t; }
    return a;
}

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
