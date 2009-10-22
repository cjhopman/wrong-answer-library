/*
 * lattice_prim.cpp
 *
 * Geometry primitives over lattices
 *
 *  Created on: 20090212
 *      Author: dhe
 *
 * All procedures are tested other than ones marked.
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

pt perpendicular(pt p) { return pt(-imag(p), real(p) ); }

// Returns nan if a == b.
double distPtLine(pt p, pt a, pt b)
{
    return (double)det(b-a, p-a) / dist(a, b);
}

// Returns dist(p,a) if a == b. 
// (change conditional to dot[ab] < 0 to return nan)
double distPtSeg(pt p, pt a, pt b)
{
    int dota = dot(b-a, p-a);
    int dotb = dot(a-b, p-b);
    if (dota <= 0)
        return dist(p, a);
    if (dotb <= 0)
        return dist(p, b);
    return abs((double)det(b-a, p-a)) / dist(a, b);
}

/* True if a-b c-d parallel.
 *  - True if a == b or c == d    */
bool isParallel(pt a, pt b, pt c, pt d)
{ return det(a-b, c-d) == 0; }

/* True if p is on segment a-b.
 *  - True at endpoints      */
bool xPtSeg(pt p, pt a, pt b)
{
    if ( a == b )            // degenerate case
        return p == a;
    return 
        det(p-a, b-a) == 0 &&
        dot(p-a, b-a) >= 0 && 
        dot(p-b, a-b) >= 0   ;
}

/* True if p is on segment a-b.
 *  - False at endpoints      */
bool xPtSeg_open(pt p, pt a, pt b)
{
    return 
        det(p-a, b-a) == 0 &&
        dot(p-a, b-a) >  0 && 
        dot(p-b, a-b) >  0   ;
}

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
bool xSegSeg_simple(pt a, pt b, pt c, pt d) 
{
    return 
        det(c-a,d-a) > 0 == det(d-b,c-b) > 0 &&
        det(a-c,b-c) > 0 == det(b-d,a-d) > 0 ;
}

void barycentric(pt p, pt a, pt b, pt c, double L[3])
{
    double t = det(a-c, b-c);
    L[0] = - (double)det(b-c, p-c) / t;
    L[1] =   (double)det(a-c, p-c) / t;
    L[2] = 1 - L[0] - L[1];
}

/* True if p is in triangle abc, using barycentric coordinates
 */
bool in_triangle_2(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return L[0] >= 0 && L[1] >= 0 && L[2] >= 0;
}

bool in_triangle_2_open(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return L[0] > 0 && L[1] > 0 && L[2] > 0;
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
