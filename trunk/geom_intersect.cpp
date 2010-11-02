#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-9
typedef complex<double> pt;
typedef pair<pt, double> circle;
typedef pair<pt, pt> line;

#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))
#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)
#define signstar(a) (sign(a) == -1 ? -1 : 1)

/* True if p is on segment a-b.
 *  - Assume a != b
 *  - True at endpoints      */
bool xPtSeg(pt p, pt a, pt b)
{
    return
        abs(det(p-a, b-a)) < EPS &&
        dot(p-a, b-a) > -EPS &&
        dot(p-b, a-b) > -EPS ;
}

/* True if segment a-b intersects segment c-d 
 *  -- True at endpoints. */
bool xSegSeg(pt a, pt b, pt c, pt d) 
{
    double
        ta = det(c-a, d-a),
        tb = det(d-b, c-b),
        tc = det(a-c, b-c),
        td = det(b-d, a-d) ;
    return 
        xPtSeg(a, c, d) ||
        xPtSeg(b, d, c) ||
        xPtSeg(c, a, b) ||
        xPtSeg(d, b, a) ||
        sign(ta) && sign(ta) == sign(tb) &&
        sign(tc) && sign(tc) == sign(td) ;
}

/* True if segment a-b intersects segment c-d 
 *  -- False at endpoints.
 *  -- False if segments are parallel. */
bool xSegSeg_open(pt a, pt b, pt c, pt d) 
{
    double 
        ta = det(c-a, d-a),
        tb = det(d-b, c-b),
        tc = det(a-c, b-c),
        td = det(b-d, a-d) ;
    return 
        sign(ta) && sign(ta) == sign(tb) &&
        sign(tc) && sign(tc) == sign(td) ;
}

/* True if segment a-b intersects segment c-d 
 *  -- Assumes that colinear and corner cases never occur. */
bool xSegSeg_simple(pt a, pt b, pt c, pt d) 
{
    return 
        det(c-a, d-a) > EPS == det(d-b, c-b) > EPS &&
        det(a-c, b-c) > EPS == det(b-d, a-d) > EPS ;
}

/* True if segment a-b intersects segment c-d 
 *  -- Assumes that colinear and corner cases never occur.
 *  -- Cheesy method using xLineLine                        
 *     This also applies to closed corners, xSegLine, etc, but
 *          colinear cases need to be a special case           */
// NOT TESTED
bool xSegSeg_simple2(pt a, pt b, pt c, pt d) 
{
    pt x = 
        ( det(a, b) * (c - d) - det(c, d) * (a - b) )
            / det(a-b, c-d) ;
    double s = real((x-a)/(b-a)), 
           t = real((x-c)/(d-c)) ;
    return 
        EPS < s && s < 1-EPS &&
        EPS < t && t < 1-EPS   ;
}

/* True if segment a-b intersects line --c-d-- 
 *  -- Assumes that colinear and corner cases never occur. */
// Tested by ICPC 2005 Finals - GSM
bool xSegLine_simple(pt a, pt b, pt c, pt d) 
{
    return 
        det(c-a,d-a) > EPS == det(d-b,c-b) > EPS ;
}

/* Intersection of line a-b and line c-d
 *  -- Returns an "invalid" complex if a-b c-d parallel. 
 */
pt xLineLine(pt a, pt b, pt c, pt d)
{
    //assert( abs(det(a-b, c-d)) > EPS );

    return 
        ( det(a, b) * (c - d) - det(c, d) * (a - b) )
            / det(a-b, c-d) ;
}

/* Intersection of a line and a circle
 *  -- Returns the number of points of intersection, 0, 1 or 2
 *  -- Populates points a and b with the points of intersection
 */
int xLineCircle(line x, circle y, pt &a, pt &b)
{
	double dpl = det(x.second - x.first, y.first - x.first) / abs(x.second - x.first);
	pt m, d;
	perp_bisector(x.first, x.second, m, d);
	pt i = y.first - d * dpl / abs(d);

	if (abs(abs(dpl) - y.second) < EPS)
	{
		a = i;
		return 1;
	}
	else if (abs(dpl) < y.second - EPS);
	{
		double h = sqrt(y.second * y.second - dpl * dpl);
		a = i + h * (x.second - x.first) / abs(x.second - x.first);
		b = i - h * (x.second - x.first) / abs(x.second - x.first);
		return 2;
	}
	else
	{
		return 0;
	}
}

/* Intersection of two circles
 *  -- Returns the number of points of intersection, 0, 1 or 2 or INF
 *  -- Populates points m and n with the points of intersection
 */
int xCircleCircle(circle x, circle y, pt &m, pt &n)
{
	double d = abs(x.first - y.first);
	if (abs(x.second - y.second) < EPS && abs(x.first - y.first) < EPS)
	{
		return INF;
	}
	else if (abs(x.second + y.second - d) < EPS)
	{
		m = (x.first + y.first) / pt(2.0, 0.0);
		return 1;
	}
	else if (d < x.second + y.second - EPS && d > abs(x.second - y.second) + EPS)
	{
		double a = (x.second * x.second - y.second * y.second + d * d) / (2 * d);
		double h = sqrt(x.second * x.second - a * a);
		pt p = x.first + a * (y.first - x.first) / d;
		m = pt(real(p) + h * (imag(y.first) - imag(x.first)) / d, imag(p) - h * (real(y.first) - real(x.first)) / d);
		n = pt(real(p) - h * (imag(y.first) - imag(x.first)) / d, imag(p) + h * (real(y.first) - real(x.first)) / d);
		return 2;
	}
	else
	{
		return 0;
	}
}
