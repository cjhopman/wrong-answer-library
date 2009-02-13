/*
 * geom_prim.cpp
 *
 * This is another set of geometry routines.
 * Significant differences from Chris's geometry.cpp are:
 *  - complex<coordinate_type> instead of pair<coordinate_type>
 *  - liberal use of 2D determinant and 2D dot product.
 *
 *  This should result in less variables and shorter code.
 *
 *  Created on: Nov 14, 2008
 *      Author: dhe
 */

#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-10

typedef complex<double> pt;

double dist2(pt a, pt b) { return norm(b-a); }
double dist(pt a, pt b) { return abs(b-a); }

/* det(a, b) is used everywhere. We implement it as a macro.
 * 
 * det(a, b) = | ax ay |
 *             | bx by |
 *   (at least in 2D)
 */

//#define det(a, b) (real(a)*imag(b) - imag(a)*real(b))
//#define dot(a, b) (real(a)*real(b) + imag(a)*imag(b))
#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))

#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)

//** NOT TESTED
pt perpendicular(pt p) { return p * polar(1.0, M_PI/2); }

// Tested.
// Returns nan if a == b.
double distPtLine(pt p, pt a, pt b)
{
    return abs(det(b-a, p-a)) / abs(b-a);
}

// Tested.
// Returns dist(p,a) if a == b. (change conditional to dot[ab] < 0 to return nan)
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
 *  - True at endpoints      */
bool xPtSeg(pt p, pt a, pt b)
{
    if ( abs(b-a) < EPS)            // check degenerate case a == b
        return abs(p-a) < EPS;
    return 
        abs(det(p-a, b-a)) < EPS &&
        dot(p-a, b-a) > -EPS && 
        dot(p-b, a-b) > -EPS ;
}

/* True if p is on segment a-b.
 *  - False at endpoints      */
bool xPtSeg_open(pt p, pt a, pt b)
{
    return 
        abs(det(p-a, b-a)) < EPS &&
        dot(p-a, b-a) > EPS && 
        dot(p-b, a-b) > EPS ;
}

/* True if segment a-b intersects segment c-d 
 *  -- True at endpoints. */
bool xSegSeg(pt a, pt b, pt c, pt d) 
{
    double
        ta = det(c-a,d-a),
        tb = det(d-b,c-b),
        tc = det(a-c,b-c),
        td = det(b-d,a-d) ;
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
 *  -- False if segments are colinear. */
bool xSegSeg_open(pt a, pt b, pt c, pt d) 
{
    double 
        ta = det(c-a,d-a),
        tb = det(d-b,c-b),
        tc = det(a-c,b-c),
        td = det(b-d,a-d) ;
    return 
        sign(ta) && sign(ta) == sign(tb) &&
        sign(tc) && sign(tc) == sign(td) ;
}

/* True if segment a-b intersects segment c-d 
 *  -- Assumes that colinear and corner cases never occur. */
bool xSegSeg_simple(pt a, pt b, pt c, pt d) 
{
    return 
        det(c-a,d-a) > EPS == det(d-b,c-b) > EPS &&
        det(a-c,b-c) > EPS == det(b-d,a-d) > EPS ;
}

/* Intersection of line a-b and line c-d
 *  -- Returns an "invalid" complex if a-b c-d parallel. (i.e. contains nan or inf)
 */
pt xLineLine(pt a, pt b, pt c, pt d)
{
    //assert( det(a-b, c-d) > EPS );

    double rx, ry;
    rx = det( pt( det(a,b), real(a-b) ),
              pt( det(c,d), real(c-d) ) );
    ry = det( pt( det(a,b), imag(a-b) ),
              pt( det(c,d), imag(c-d) ) );

    return pt(rx, ry) / det(a-b, c-d);
}

void barycentric(pt p, pt a, pt b, pt c, double L[3])
{
    double t = det(a-c, b-c);
    L[0] = - det(b-c, p-c) / t;
    L[1] =   det(a-c, p-c) / t;
    L[2] = 1 - L[0] - L[1];
}

/* True if p is in triangle abc, using barycentric coordinates
 *  - Tested              */
bool in_triangle_2(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return L[0] > -EPS && L[1] > -EPS && L[2] > -EPS;
}

bool in_triangle_2_open(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return L[0] > EPS && L[1] > EPS && L[2] > EPS;
}

/* True if p is in triangle abc
 *  - True if p is on edge or corner */
bool in_triangle(pt p, pt a, pt b, pt c)
{
    int z1 = sign(det(p-a, b-a)),
        z2 = sign(det(p-b, c-b)),
        z3 = sign(det(p-c, a-c)) ;
    int t = z1 ? z1 : z2 ? z2 : z3 ;
    return
        (!z1 || z1 == t) &&
        (!z2 || z2 == t) &&
        (!z3 || z3 == t)   ;
}

/* True if p is in triangle abc
 *  - False if p is on edge or corner */
bool in_triangle_open(pt p, pt a, pt b, pt c)
{
    int z1 = sign(det(p-a, b-a)),
        z2 = sign(det(p-b, c-b)),
        z3 = sign(det(p-c, a-c)) ;
    return z2 && z1 == z2 && z2 == z3 ;
}


//** NOT TESTED
// TODO: remove! why is this even here?
int gcd(int a, int b)
{
    while (b != 0)
    { int t=b; b = a%b; a=t; }
    return a;
}
