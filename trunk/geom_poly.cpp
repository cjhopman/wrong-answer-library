/*
 * geom_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include <vector>
#include <complex>

using namespace std;

#define EPS 1E-9
#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))
#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)
#define signstar(a) (sign(a) == -1 ? -1 : 1)

typedef complex<double> pt;
typedef pair<pt, pt> line;
typedef vector<pt> polygon;
typedef line seg;

/*
 * Assume V[0] == V[-1] 
 */
double signed_area(polygon &V)
{
	double A = 0.0;
	for (unsigned i = 1; i < V.size(); i++)
		A += det(V[i - 1], V[i]);
	return A / 2;
}

/*
 * Assume V[0] == V[-1] 
 */
pt centroid(polygon &V)
{
	pt c = pt(0.0, 0.0);
	for (unsigned i = 1; i < V.size(); i++)
		c += (V[i - 1] + V[i]) * pt(det(V[i - 1], V[i]), 0.0);
	return c / pt(6 * signed_area(V), 0.0);
}

#define det(a, b) imag(conj(a)*(b))

/* Returns 2 * (area of polygon V)
 *  - Assumes V[0] == V[-1]
 */
double area_polygon(polygon &V)
{
    double A = 0.0;
    for (unsigned i = 1; i < V.size(); i++)
        A += det(V[i - 1], V[i]);
    return abs(A);
}

/*  - Assumes convex V in ccw order
 *  - Assumes V[0] == V[-1]
 */
bool inside_convex(pt p, polygon& V)
{
    for (unsigned i = 1; i < V.size(); i++)
        if (det(V[i] - V[i - 1], p - V[i - 1]) < -EPS)
            return false;
    return true;
}

/*
 * Tests whether p is in simple polygon V
 *  - Assumes V[0] == V[-1]
 *  - Assumes p does not intersect V
 *  - Assumes segment p-q does not intersect corners
 *  - Assumes q is large enough
 */
bool inside_polygon(pt p, polygon& V)
{
    pt q = polar(1e8, 1.2345);
    int s = 0;
    for (int i = 1; i < V.size(); i++)
        s += xSegSeg(p, q, V[i - 1], V[i]);
    return s % 2 == 1;
}


/*$*/
int main()
{
	return 0;
}
/*$*/
