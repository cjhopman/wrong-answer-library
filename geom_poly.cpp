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

/* Returns 2 * (area of polygon V) */
//** NOT TESTED
double area_polygon(polygon &V)
{
    double A = 0.0;

    for (int i = 0; i < V.size(); i++)
        A += det( V[i], V[(i+1) % V.size()] );

    return abs(A);
}

// vertices should be in counterclockwise order, with a0 == an
//** NOT TESTED
bool inside_convex(pt p, polygon& V)
{
	for (unsigned i = 0; i < V.size(); i++)
        if ( det( V[(i+1) % V.size()] - V[i], p - V[i] ) < 0 )
            return false;
	return true;
}


