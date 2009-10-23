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

#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))

#define sign(a) (a == 0 ? 0 : a > 0 ? 1 : -1)

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
	int n[3] = {0, 0, 0};
	n[1 + sign(det(p - a, b - a))]++;
	n[1 + sign(det(p - b, c - b))]++;
	n[1 + sign(det(p - c, a - c))]++;
    return !n[0] || !n[2];
}

/* True if p is in triangle abc
 *  - False if p is on edge or corner */
bool in_triangle_open(pt p, pt a, pt b, pt c)
{
	int n[3] = {0, 0, 0};
	n[1 + sign(det(p - a, b - a))]++;
	n[1 + sign(det(p - b, c - b))]++;
	n[1 + sign(det(p - c, a - c))]++;
    return n[0] == 3 || n[2] == 3;
}

