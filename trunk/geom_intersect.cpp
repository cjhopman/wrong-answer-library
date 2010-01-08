#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-9
typedef complex<double> pt;

#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))

#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)

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

