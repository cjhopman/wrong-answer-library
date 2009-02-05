/*
 * geometry.cpp
 *
 *  Created on: Nov 7, 2008
 *      Author: Chris
 */

#include <cmath>
#include <algorithm>
#include <cerrno>
#include <vector>

using namespace std;

#define EPS 1e-10

typedef double coordinate_type;
typedef pair<coordinate_type, coordinate_type> point;
typedef vector<point> polygon;

double dist2(double x0, double y0, double x1, double y1)
	{ return (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0); }
double dist(double x0, double y0, double x1, double y1)
	{ return sqrt(dist2(x0, y0, x1, y1)); }


void barycentric(double x0, double y0, double x1, double y1, double x2, double y2,
		double px, double py, double& lambda1, double& lambda2, double& lambda3) {
	double rx = px - x2, ry = py - y2;
	double a = x0 - x2, b = x1 - x2, c = y0 - y2, d = y1 - y2;
	double det = a * d - b * c;
	lambda1 = (d * rx - b * ry) / det;
	lambda2 = (a * ry - c * rx) / det;
	lambda3 = 1 - lambda1 - lambda2;
}

bool in_triangle(double x0, double y0, double x1, double y1, double x2, double y2,
		double px, double py, double& l1, double& l2, double& l3) {
	barycentric(x0, y0, x1, y1, x2, y2, px, py, l1, l2, l3);
	return l1 > EPS && l2 > EPS && l3 > EPS;
}

//** NOT TESTED
bool on_triangle(double x0, double y0, double x1, double y1, double x2, double y2,
		double px, double py, double& l1, double& l2, double& l3) {
	in_triangle(x0, y0, x1, y1, x2, y2, px, py, l1, l2, l3);
	return (l1 > -EPS && l2 > -EPS && l3 > -EPS) && (l1 < EPS || l2 < EPS || l3 < EPS);
}

double polar(double x, double y) {
	if (fabs(x) < EPS && fabs(y) < EPS) return 0.0/0.0;
	return atan2(y, x);
}

//** NOT TESTED
double distance_to_line(double px, double py, double ax, double ay, double bx, double by,
		double& cx, double& cy) {
	double sx0 = px - ax, sy0 = py - ay, sx1 = bx - ax, sy1 = by - ay;
	double proj = (sx0 * sx1 + sy0 * sy1) / (sx1 * sx1 + sy1 * sy1);
	cx = ax + proj * sx1;
	cy = ay + proj * sy1;
	return dist(px, py, cx, cy);
}

double distance_to_line_segment(double px, double py, double ax, double ay, double bx, double by,
		double& cx, double& cy) {
	double sx0 = px - ax, sy0 = py - ay, sx1 = bx - ax, sy1 = by - ay;
	double proj = (sx0 * sx1 + sy0 * sy1) / (sx1 * sx1 + sy1 * sy1);
	if (proj < 0) {
		cx = ax; cy = ay;
	} else if (proj > 1) {
		cx = bx; cy = by;
	} else {
		cx = ax + proj * sx1;
		cy = ay + proj * sy1;
	}
	return dist(px, py, cx, cy);
}


// 0 - no intersection, 1 - point, 2 - line
int line_intersection(double x1, double y1, double x2, double y2, double x3, double y3,
		double x4, double y4, double& cx, double& cy) {
	double d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	double ua = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	double ub = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
	if (fabs(d) < EPS)	return fabs(ua) < EPS && fabs(ub) < EPS ? 2: 0;
	ua /= d;
	cx = x1 + ua * (x2 - x1);
	cy = y1 + ua * (y2 - y1);
	return 1;
}

int line_segment_intersection(double x1, double y1, double x2, double y2,
		double x3, double y3, double x4, double y4, double& cx, double& cy) {
	// line1 = P1 + ua * (P2 - P1), line2 = P3 + ub * (P4 - P3)
	double d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
	double ua = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	double ub = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
	ua /= d; ub /= d;
	if (ua < -EPS || ua > 1 + EPS || ub < EPS || ub > 1 + EPS || fabs(d) < EPS) return 0;
	cx = x1 + ua * (x2 - x1), cy = y1 + ua * (y2 - y1);
	return 1;
}

double circle_3_points(double x1, double y1, double x2, double y2, double x3, double y3,
		double x4, double y4, double& cx, double& cy) {
	if (x3 == x2 && x2 == x1) return -1;

	if (x3 == x2) { swap(x1, x2); swap(y1, y2); }
	if (x1 == x2) { swap(x1, x3); swap(y1, y3); }

	double ma = (y2 - y1) / (x2 - x1), mb = (y3 - y2) / (x3 - x2);

	if (mb == ma) return -1;

	cx = (ma * mb * (y1 - y3) + mb * (x1 + x2) - ma * (x2 + x3)) / (2 * (mb - ma));
	cy = ma != 0 ? ((x1 + x2 - 2 * cx) / ma + y1 + y2) / 2
			: ((x2 + x3 - 2 * cx) / mb + y2 + y3) / 2;
	return dist(cx, cy, x1, y1);
}

// a will hold vertices x0,x1,...,xn,x0
void convex(polygon& a) {
	int first = 0;
	for (int i = 1; i < a.size(); i++)
		first = a[first].second < a[i].second || a[first].second == a[i].second
			&& a[first].first > a[i].first ? i : first;
	polygon b;
	double p = -10; int prev = first, next = -1;
	b.push_back(a[first]);
	while (next != first) {
		double n_val = 10;
		for (int i = 0; i < a.size(); i++) {
			if (i == prev) continue;
			double v = atan2(a[i].second - a[prev].second, a[i].first - a[prev].first);
			if (v > p - EPS && v < n_val) { n_val = v; next = i; }
		}
		b.push_back(a[next]);
		p = n_val; prev = next;
	}
	swap(a, b);
}

// vertices should be in counterclockwise order, with a0 == an
bool inside_convex(point p, polygon& a) {
	for (unsigned i = 1; i < a.size(); i++) {
		if ((a[i].first - a[i - 1].first) * (p.second - a[i - 1].second)
				- (a[i].second - a[i - 1].second) * (p.first - a[i - 1].first) < 0)
			return false;
	}
	return true;
}

// a0 == an, returns area * 2
double area2(polygon& a) {
	double area = 0;
	for(unsigned i = 1; i < a.size(); i++)
		area += (a[i - 1].first * a[i].second) - (a[i - 1].second * a[i].first);
	return area;
}

double great_circle(double lat1, double lon1, double lat2, double lon2) {
	lat1 *= M_PI / 180; lat2 *= M_PI / 180; lon1 *= M_PI / 180; lon2 *= M_PI / 180;
	return acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2) + sin(lat1) * (sin(lat2)));
}

int main() { return 0; }





