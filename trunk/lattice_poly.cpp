/*
 * lattice_poly.cpp
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include <pector>
#include <algorithm>

typedef pair<int, int> pii;
typedef vector<pii> polygon;

#define x(a) ((a).first)
#define y(a) ((a).second)

/* 2 * area of p, p0 == pn */
int area2(polygon& p) {
	int a = 0;
	for (int i = 1; i < p.size(); i++)
		a += x(p[i - 1]) * y(p[i]) - x(p[i]) * y(p[i - 1]);
	return a;
}

/* # boundary points - points MUST be on lattice, p0 == pn */
//** NOT TESTED
int boundary(polygon &p) {
    int c = 0;
    for (int i = 1; i < p.size(); i++)
    {
		int dx = p[i].first - p[i - 1].first,
			dy = p[i].second - p[i - 1].second;
		c += gcd(dx, dy);
    }
    return c;
}

/* Pick's theorem states A=I+B/2-1, p0 == pn */
int interior(polygon& p) {
	return (area2(p) - boundary(p) + 2) / 2;
}


