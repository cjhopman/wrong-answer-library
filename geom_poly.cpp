/*
 * geom_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include "geom_prim.cpp"
#include <vector>
#include <deque>
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

bool dict_less(pt a, pt b) {
    if (abs(imag(a - b)) < EPS)
        return real(a) < real(b);
    return imag(a) < imag(b);
}

struct graham_sort {
    pt p;
    bool operator() (pt a, pt b) {
        double det = det(a-p, b-p);
        return abs(det) < EPS ? norm(a-p) < norm(b-p) : det < -EPS;
    }
};

/*
 * Creates a convex hull using Graham scan
 *
 *  - Outputs a convex hull containing points in 
 *                      counterclockwise order
 *                                                               */
//** NOT TESTED
polygon graham_scan(polygon V) // pass by value since we sort V
{
    deque<pt> s;               // we use deques because it's less typing
    pt p = *min_element(V.begin(), V.end(), dict_less);

    graham_sort gs = { p };
    sort(V.begin(), V.end(), gs);

    for (int i = 0; i < V.size(); i++)
    {
        while (s.size() >= 2 && det(s[1] - s[0], V[i]-s[0]) )
            s.pop_front();
        s.push_front(V[i]);
    }
    return polygon(s.begin(), s.end());
}
