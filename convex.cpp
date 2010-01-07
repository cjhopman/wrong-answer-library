/*$
 * TESTED UVA 109 (with integers)
 * TESTED ICPC WORLD 2009 Deer-proof Fence
 $*/

#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>

using namespace std;

#define EPS 1e-8
#define det(a, b) imag(conj(a) * (b))

typedef complex<double> pt;
typedef vector<pt> polygon;

pt pv;  // pivot point
bool comp_pivot(pt a, pt b)
{
    double d = det(a - pv, b - pv);
    if (abs(d) < EPS)
        return norm(a - pv) < norm(b - pv);
    else
        return d > EPS;
}

bool comp_lex(pt a, pt b)
{
    if (abs(real(a - b)) < EPS)
        return imag(b - a) > EPS;
    else
        return real(b - a) > EPS;
}

/* Graham scan 
 *  - Correct with collinear points
 *  - P.size >= 2
 */
polygon convex_hull(polygon P)    // pass by value
{
    swap(P[0], *min_element(P.begin(), P.end(), comp_lex));
    pv = P[0];
    sort(P.begin(), P.end(), comp_pivot);

    int m = 2;
    for (int i = 2; i < P.size(); i++) {
        while (m >= 2 && det(P[m - 1] - P[m - 2], P[i] - P[m - 1]) < EPS)
            m--;
        P[m++] = P[i];
    }
    P.erase(P.begin() + m, P.end());
    return P;
}

/*$*/
/* ICPC 2009 Final Fences */

#include <cstdio>
#include <iostream>
int N;
int main1(int argc, char **argv)
{
    for (int caseno = 1; ; caseno++)
    {
        polygon Z;
        cin >> N;
        if (N == 0)
            break;
        for (int i = 0; i < N; i++)
        {
            double xi, yi;
            cin >> xi >> yi;
            Z.push_back(pt(xi, yi));
        }
        polygon Z2 = convex_hull(Z);
        for (int i = 0; i < Z2.size(); i++)
            cout << Z2[i];
        cout << endl;
    }
    return 0;
}

/*$*/
