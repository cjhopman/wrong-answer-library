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

/* Returns 2 * (area of polygon V) */
//** NOT TESTED
double area_polygon(polygon &V)
{
    double A = 0.0;
    V.push_back(*V.begin());

    for (int i = 1; i < V.size(); i++)
        A += det(V[i-1], V[i]);

    V.pop_back();
    return abs(A);
}

// vertices should be in counterclockwise order, with a0 == an
//** NOT TESTED
bool inside_convex(pt p, polygon& V)
{
    V.push_back(*V.begin());
	for (unsigned i = 1; i < V.size(); i++)
        if ( det(V[i] - V[i-1], p - V[i-1]) < 0 )
            return false;
	return true;
}
/* Number of boundary points - points in V MUST be on lattice! */
//** NOT TESTED
int boundary(polygon &V)
{
    int c = 0;
    V.push_back(*V.begin());
    for (int i = 1; i < V.size(); i++)
    {
        pt t = V[i] - V[i-1];
        c += abs(gcd( round(real(t)), round(imag(t)) ));
    }
    V.pop_back();
    return c;
}

/*
 * Pick's theorem states A=I+B/2-1
 */

