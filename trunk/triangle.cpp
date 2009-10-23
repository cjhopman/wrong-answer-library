/** Triangle algorithms
 * barycentric coordinates, interior test...
 */

#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-10

typedef complex<double> pt;

#define det(a, b) imag(conj(a)*(b))
#define dot(a, b) real(conj(a)*(b))

#define sign(a) (abs(a) < EPS ? 0 : a > 0 ? 1 : -1)

void barycentric(pt p, pt a, pt b, pt c, double L[3])
{
    double t = det(a-c, b-c);
    L[0] = - det(b-c, p-c) / t;
    L[1] =   det(a-c, p-c) / t;
    L[2] = 1 - L[0] - L[1];
}

/* True if p is in triangle abc, using barycentric coordinates */
bool in_triangle_2(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return
        L[0] > -EPS &&
        L[1] > -EPS &&
        L[2] > -EPS   ;
}

bool in_triangle_2_open(pt p, pt a, pt b, pt c)
{
    double L[3];
    barycentric(p, a, b, c, L);
    return
        L[0] > EPS &&
        L[1] > EPS &&
        L[2] > EPS   ;
}


/* True if p is in triangle abc
 *  - True if p is on edge or corner */
bool in_triangle(pt p, pt a, pt b, pt c)
{
	int n[3] = {0};
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

