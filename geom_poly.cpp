/*
 * geom_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include <vector>
#include <algorithm>

#define x(a) ((a).first)
#define y(a) ((a).second)
#define det(a, b) (x(a) * y(b) - x(b) * y(a))
#define ccw(a, b, c) det(a - b, c - b)

typedef pair<double, double> pt;
typedef vector<pt> polygon;

/* Returns 2 * (area of polygon V), a0 must == an
 * TESTED integers: UVA 109
 */

double area_polygon(polygon &V)
{
    double A = 0.0;
    for (int i = 1; i < V.size(); i++)
        A += det(V[i - 1], V[i]);
    return abs(A);
}

/* vertices should be in counterclockwise order, with a0 == an
 * TESTED integers: UVA 109
 */

bool inside_convex(pt p, polygon& V)
{
	for (unsigned i = 1; i < V.size(); i++)
        if (ccw(V[i - 1], V[i], p) < 0)
            return false;
	return true;
}

/* True if segment a-b crosses V
 *   - True at edge and corner cases */
//** NOT TESTED
bool xSegPoly(pt a, pt b, polygon V)
{
    return 0;
}

/* True if line a-b crosses V
 *   - True at edge and corner cases */
//** NOT TESTED
bool xLinePoly(pt a, pt b, polygon V)
{
    return 0;
}
