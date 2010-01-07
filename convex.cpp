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
int N, M;

double calc_perim(const polygon &P)
{
    double S = 0.0;
    for (int i = 0; i < P.size(); i++)
        S += abs(P[i] - P[(i+1) % P.size()]);
    return S + 2 * M_PI * M;
}

polygon Z;
double D[1 << 9];

double calc_cost(int X)
{
    polygon P;
    for (int k = 0; k < N; k++)
        if (X & (1 << k))
            P.push_back(Z[k]);

    if (P.size() != 1)
        P = convex_hull(P);
    double d = calc_perim(P);

    int m[9];
    int j = 0;
    for (int k = 0; k < N; k++)
        if (X & 1 << k)
            m[j++] = k;

    for (int i = 1; i < (1 << __builtin_popcount(X)) - 1; i++)
    {
        int X2 = 0;
        for (int k = 0; k < j; k++)
            if (i & 1 << k)
                X2 |= 1 << m[k];

        int X3 = X - X2;
        d = min(d, D[X2] + D[X3]);
    }
    return d;
}

void do_dp()
{
    for (int i = 1; i < 1 << N; i++)
        D[i] = calc_cost(i);
}

int main(int argc, char **argv)
{
    for (int caseno = 1; ; caseno++)
    {
        Z.clear();
        cin >> N >> M;
        if (N == 0)
            break;

        for (int i = 0; i < N; i++)
        {
            int xi, yi;
            cin >> xi >> yi;
            Z.push_back(pt(xi, yi));
        }

        do_dp();

        printf("Case %d: ", caseno);
        printf("length = %.2f\n", D[(1 << N) - 1]);
    }
    return 0;
}
/*$*/
