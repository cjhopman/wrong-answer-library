/*
 * lattice_prim.cpp
 *
 * Geometry primitives over lattices
 *
 *  Created on: 20090212
 *      Author: dhe
 */

#include <cmath>
#include <complex>

using namespace std;

typedef complex<int> pt;

int dist2(pt a, pt b) { return norm(b-a); }
double dist(pt a, pt b) { return sqrt(norm(b-a)); }

#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))

#define sign(a) (a == 0 ? 0 : a > 0 ? 1 : -1)

//** NOT TESTED
//pt perpendicular(pt p) { return p * polar(1.0, M_PI/2); }

//** NOT TESTED
// Returns nan if a == b.
double distPtLine(pt p, pt a, pt b)
{
    return (double)det(b-a, p-a) / dist(a, b);
}

//** NOT TESTED
// Returns dist(p,a) if a == b. (change conditional to dot[ab] < 0 to return nan)
double distPtSeg(pt p, pt a, pt b)
{
    int dota = dot(b-a, p-a);
    int dotb = dot(a-b, p-b);
    if (dota < 0)
        return dist(p, a);
    if (dotb < 0)
        return dist(p, b);
    return det(b-a, p-a) / dist(a, b);
}

//** NOT TESTED
/* True if a-b c-d parallel.
 *  - True if a == b or c == d    */
bool isParallel(pt a, pt b, pt c, pt d)
{ return det(a-b, c-d) == 0; }

//** NOT TESTED
/* True if p is on segment a-b.
 *  - True at endpoints      */
bool xPtSeg(pt p, pt a, pt b)
{
    return 
        det(p-a, b-a) == 0 && 
        dot(p-a, b-a) >= 0 && 
        dot(p-b, a-b) >= 0   ;
}

//** NOT TESTED
/* True if segment a-b intersects segment c-d 
 *  -- True at endpoints. */
bool xSegSeg(pt a, pt b, pt c, pt d) 
{
    int 
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

//** NOT TESTED
/* True if segment a-b intersects segment c-d 
 *  -- False at endpoints.
 *  -- False if segments are parallel. */
bool xSegSeg_open(pt a, pt b, pt c, pt d) 
{
    int
        ta = det(c-a,d-a),
        tb = det(d-b,c-b),
        tc = det(a-c,b-c),
        td = det(b-d,a-d) ;
    return 
        sign(ta) && sign(ta) == sign(tb) &&
        sign(tc) && sign(tc) == sign(td) ;
}

/* True if segment a-b intersects segment c-d 
 *  -- Assumes that edge and corner cases never occur. */
// Not tested
bool xSegSeg_simple(pt a, pt b, pt c, pt d) 
{
    return 
        det(c-a,d-a) > 0 == det(d-b,c-b) > 0 &&
        det(a-c,b-c) > 0 == det(b-d,a-d) > 0 ;
}

//** NOT TESTED
/* Intersection of line a-b and line c-d
 *  -- Returns an "invalid" complex if a-b c-d parallel. (i.e. contains nan or inf)
 */
//TODO: remove?
/*
pt xLineLine(pt a, pt b, pt c, pt d)
{
    //assert( det(a-b, c-d) > 0 );

    double rx, ry;
    rx = det( pt( det(a,b), real(a-b) ),
              pt( det(c,d), real(c-d) ) );
    ry = det( pt( det(a,b), imag(a-b) ),
              pt( det(c,d), imag(c-d) ) );

    return pt(rx, ry) / det(a-b, c-d);
}
*/

/* copied from Chris's code; not tested */
/*
void barycentric(pt _a, pt _b, pt _c, pt _p, double &L1, double &L2, double &L3)
{
    pt a = _a - _c, b = _b - _c, p = _p - _c;
    L1 = - det(b, p) / det(a, b);
    L2 =   det(a, p) / det(a, b);
    L3 = 1 - L1 - L2;
}
*/

/* copied from Chris's code; not tested */
/*
bool in_triangle(pt _p, pt _a, pt _b, pt _c)
{
    double L1, L2, L3;
    barycentric(_a, _b, _c, _p, L1, L2, L3);
    return L1 > EPS && L2 > EPS && L3 > EPS;
}
*/

//** NOT TESTED
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

//** NOT TESTED
/* True if p is in triangle abc
 *  - False if p is on edge or corner */
bool in_triangle_open(pt p, pt a, pt b, pt c)
{
    int z1 = sign(det(p-a, b-a)),
        z2 = sign(det(p-b, c-b)),
        z3 = sign(det(p-c, a-c)) ;
    return z2 && z1 == z2 && z2 == z3 ;
}
