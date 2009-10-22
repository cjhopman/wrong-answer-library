/* Convex hull
 * TESTED integers: UVA 109
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define EPS 1e-8

typedef pair<double, double> pdd;
typedef vector<pdd> polygon;

#define x(a) ((a).first)
#define y(a) ((a).second)

double ccw(pdd& a, pdd& b, pdd& c) {
	return (x(b) - x(a)) * (y(c) - y(a)) - (y(b) - y(a)) * (x(c) - x(a));
}

pdd ps;
bool comp(pdd a, pdd b) {
	return atan2(y(a) - y(ps), x(a) - x(ps))
		< atan2(y(b) - y(ps), x(b) - x(ps));
}

polygon convex(polygon p) {
	swap(p[0], *min_element(p.begin(), p.end()));
	ps = p[0];
	sort(p.begin() + 1, p.end(), comp);
	p.push_back(p[0]);

	int m = 3;
	for (int i = 3; i < p.size(); i++) {
		while (m > 1 && ccw(p[m - 2], p[m - 1], p[i]) < EPS) m--;
		swap(p[m++], p[i]);
	}
	return polygon(p.begin(), p.begin() + m);
}

