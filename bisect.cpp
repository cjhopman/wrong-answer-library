/*
 * bisect.cpp
 *
 *  Created on: Nov 12, 2008
 *      Author: Chris
 */

#include <iostream>
#include <cmath>

#define EPS 1e-3

double p, q, r, s, t, u;

double test(double val) {
	return p * exp(-val) + q * sin(val) + r * cos(val) + s * tan(val) + t * val * val + u;
}

double bisect(double low, double high, double low_val, double high_val, double prec) {
	if (high - low < prec) return low;
	double mid = (high + low) / 2;
	double mid_val = test(mid);
	return mid_val * low_val < 0 ? bisect(low, mid, low_val, mid_val, prec)
			: bisect(mid, high, mid_val, high_val, prec);
}

int main_bisect() {
	while (scanf("%lf %lf %lf %lf %lf %lf", &p, &q, &r, &s, &t, &u) == 6) {
		double x = test(0), y = test(1);
		if (x * y > 0) printf("No solution\n");
		else if (fabs(x) < EPS) printf("0.0000\n");
		else printf("%.4lf\n", bisect(0, 1, test(0), test(1), 1e-9));
	}
}
