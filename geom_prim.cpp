/*$
 * All procedures are tested other than ones marked.
$*/

#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-9
typedef complex<double> pt;

#define det(a, b) imag(conj(a)*(b))   // cf right-hand rule, cross-prod, 3x3 det
#define dot(a, b) real(conj(a)*(b))

pt perpendicular(pt p) { return p * polar(1.0, 0.5 * M_PI); }

/* True if a-b c-d parallel.
 *  - True if a == b or c == d    */
bool isParallel(pt a, pt b, pt c, pt d)
{ return abs(det(a-b, c-d)) < EPS; }

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
pt circle_3_points(pt a, pt b, pt c)
{
    pt m1, d1, m2, d2;
    perp_bisector(a, b, m1, d1);
    perp_bisector(a, c, m2, d2);
    return xLineLine(m1, m1 + d1, m2, m2 + d2);
}

/* 
 * Returns great circle distance of two points on unit sphere
 *  - Points are (azimuth, inclination) coords in radians
 *  - Unstable at antipodal points
 */
double great_circle_dist(double th1, double phi1, double th2, double phi2)
{
#define haversine(x) pow(sin((x) / 2), 2.0)
    double z = haversine(phi1 - phi2) + sin(phi1) * sin(phi2) * haversine(th1, th2);
    return 2 * acos(sqrt(z));
}

/*
spherical coordinate system:
 - math convention, not physics
(r = radius, th = azimuth, phi = inclination)
 - azimuth is right-hand from x-axis
 - elevation = pi/2 - inclination
 - 0 <= phi <= pi
 - 0 <= th < 2 * pi

r^2 = x^2 + y^2 + z^2
th = atan2(y, x)
phi = acos(z / r)

geographic coordinate system (spherical approximation):
(latitude, longitude)
latitude = elevation from celestial equator
longitude = right-hand azimuth from greenwich
*/

/*
 * Descartes' Theorem:
 * Given four mutually tangent circles with curvatures k1, k2, k3, k4, 
 * (k1 + k2 + k3 + k4) ^ 2 = 2 * (k1 ^ 2 + k2 ^ 2 + k3 ^ 2 + k4 ^ 2)
 */
