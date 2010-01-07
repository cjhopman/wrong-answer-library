/*
 * All procedures are tested other than ones marked.
 */

#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-9
typedef complex<double> pt;

#define det(a, b) imag(conj(a)*(b))   // cf right-hand rule, cross-prod, 3x3 det
#define dot(a, b) real(conj(a)*(b))
#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)

pt perpendicular(pt p) { return p * polar(1.0, 0.5 * M_PI); }

// Returns nan if a == b.
double distPtLine(pt p, pt a, pt b)
{
    return abs(det(b-a, p-a)) / abs(b-a);
}

// Returns dist(p,a) if a == b. 
// (change conditional to dot[ab] < 0 to return nan)
double distPtSeg(pt p, pt a, pt b)
{
    double dota = dot(b-a, p-a);
    double dotb = dot(a-b, p-b);
    if (dota < EPS)
        return abs(p-a);
    if (dotb < EPS)
        return abs(p-b);
    return abs(det(b-a, p-a)) / abs(b-a);
}

/* True if a-b c-d parallel.
 *  - True if a == b or c == d    */
bool isParallel(pt a, pt b, pt c, pt d)
{ return abs(det(a-b, c-d)) < EPS; }

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

/* Returns the perpendicular bisector of segment a-b
 *  - The segment with endpoints m and m+d will be a perpendicular bisector.
 *  - d == 0 iff a == b                                                      */
void perp_bisector(pt a, pt b, pt &m, pt &d)
{
    m = (a + b) / pt(2, 0);
    d = (b - a) * pt(0, 1);
}

/*
 * Returns the center of circle touching three points
 *   - Assumes {a, b, c} distinct
 * NOT TESTED
 */
double circle_3_points(pt a, pt b, pt c)
{
    pt m1, d1, m2, d2;
    perp_bisector(a, b, m1, d1);
    perp_bisector(a, c, m2, d2);
    return xLineLine(m1, m1 + d1, m2, m2 + d2);
}

// takes latitude/longitude in degrees as normally specified
double great_circle_dist(double lat1, double lon1, double lat2, double lon2) {
	lat1 *= M_PI / 180; lat2 *= M_PI / 180;
	lon1 *= M_PI / 180; lon2 *= M_PI / 180;
	return acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2)
			+ sin(lat1) * (sin(lat2)));
}

/* 
 * Returns great circle distance of two points on unit sphere
 *  - Points are (inclination, azimuth) coords in radians
 *  - Unstable at antipodal points
 */
double great_circle_dist(double th1, double phi1, double th2, double phi2)
{
#define haversine(x) pow(sin((x) / 2), 2.0)
    double z = haversine(th1 - th2) + sin(th1) * sin(th2) * haversine(phi1 - phi2);
    return 2 * acos(sqrt(z));
}

/*
spherical coordinate system:
(r = radius, th = inclination, phi = azimuth)
 - azimuth is right-hand from x-axis
 - elevation = pi/2 - inclination
 - 0 <= th <= pi
 - 0 <= phi < 2 * pi

r^2 = x^2 + y^2 + z^2
th = acos(z / r)
phi = atan2(y, x)

geographic coordinate system (spherical approximation):
(latitude, longitude)
latitude = elevation from celestial equator
longitude = right-hand azimuth from greenwich
*/
