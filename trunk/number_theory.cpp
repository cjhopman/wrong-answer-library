/*$
number theory 
$*/

#include <cmath>
#include <map>
#include <vector>
#include <cstdlib>  // labs
#include <stdint.h>

using namespace std;

/* Division algorithm, but works for negative dividend and divisors.
 * Correctness of div() and ldiv() is platform specfiic!
 *   - Mandate: y = d * x + r
 * - Tested using Bipartite Numbers
 */
ldiv_t div_correct(long y, long x)
{
    ldiv_t v = ldiv(y, x);
    if (y < 0 && v.rem != 0) {
        v.quot -= 1;
        v.rem += labs(x);
    }
    return v;
}

/*$
pii euclid(int a, int b) {
	if (!b) return pii(0, 1);
	pii t = euclid(b, a % b);
	return pii(t.second, t.first - t.second * (a / b));
}

int gcd(int a, int b) {
	pii e = euclid(abs(a), abs(b));
	return abs(a) * e.first + abs(b) * e.second;
}

int extended_gcd(int a, int b) {
	pii t = euclid(abs(a), abs(b));
	t.first *= 1 + -2 * (a < 0);
	t.second *= 1 + -2 * (b < 0);
	return t;
}
$*/

/* - At least one input must be non-zero.
 * - Output is always non-negative.
 * - Tested using Bipartite Numbers
 */
long gcd(long a, long b)
{
    while (b != 0)
    { long t=b; b = div_correct(a, b).rem; a=t; }
    return a;
}

long lcm(long a, long b) { return a / gcd(a, b) * b; }

/* - At least one input must be non-zero.
 * - Output: return.first should be the closest to 0, and may be negative.
 * - Tested using Bipartite Numbers
 */
pair<long,long> extended_gcd(long a, long b)
{
    if (a % b == 0)
        return pair<long,long>(0, 1);
    else {
        ldiv_t v = div_correct(a, b);
        pair<long,long> t = extended_gcd(b, v.rem);
        return pair<long,long>(t.second, t.first - t.second * v.quot);
    }
}

/*
 * Calculates x s.t. a * x \equiv 1 (\mod n).
 * Assumes x exists, i.e. gcd(a, n) == 1.
 */
// NOT TESTED
long mult_inverse(long a, long n)
{
    return div_correct(extended_gcd(a, n).first, n).rem;
}

/*
 *    Let d = \gcd(a, n) .
 *    Then a * x \equiv b (\mod n) has d solutions if d \div b, and zero
 *    solutions otherwise.
 *     - Input: 0 <= a, b < n.
 *  Tested using Bipartite Numbers
 */
vector<long> lin_cong(long a, long b, long n)
{
    vector<long> X;
    long d = gcd(a, n);
    if (b % d == 0) {
        long x = extended_gcd(a, n).first * b / d;
        for (int i = 0; i < d; i++) {
            X.push_back(div_correct(x, n).rem);
            x += n / d;
        }
    }
    return X;
}

/* Chinese remainder theorem
 *  - assume n's are pairwise relatively prime
 */
// NOT TESTED
long crt(long *a, long *n, long r)
{
    long N = 1;
    for (int k = 0; k < r; k++)
        N *= n[k];

    long s = 0;
    for (int k = 0; k < r; k++)
    {
        long p = N / n[k];
        long x = extended_gcd(p, n[k]).first;
        s += a[k] * p * x;
        s %= N;
    }
    return s;
}


//** NOT TESTED
/* Calculates b ^ e */
long ipow(long b, long e)
{
    long r = 1;
    for ( ; e; e >>= 1) {
        if (e & 1)
            r *= b;
        b *= b;
    }
    return r;
}

//** NOT TESTED
/* Calculates b ^ e (mod m) */
long mod_exp(long b, long e, int m)
{
    long r = 1;
    for ( ; e; e >>= 1) {
        if (e & 1)
            r = (r * b) % m;
        b *= b;
        b %= m;
    }
    return r;
}

/*
 * A small, non-inclusive list of primes:
 * 3, 79, 83, 89, 97, 101, 499, 503, 991, 997, 1009, 2477, 2503, 4993, 4999,
 * 5003, 9973, 10007, 99991, 100003, 999983, 1000003, 1299827
 */

/*
 * Asymptotic growth of primes (PNT):
 *         p(n) ~ x/ln(x)
 */

map<long,long> trial_factor(long n)
{
    map<long,long> f;
    for (long i = 2; i <= sqrt(n); i++)
        while (n % i == 0)
        {
            n /= i;
            f[i] += 1;
        }
    if (n > 1)
        f[n] += 1;
    return f;
}

/* finds all primes less than n */
void sieve(int n, vector<int>& p) {
	vector<bool> s(n, 1);
	int i = 2;
	for (; i * i < n; i++) {
		if (!s[i]) continue;
		p.push_back(i);
		for (int j = i * i; j < n; j += i) s[j] = 0;
	}
	for (i = i & 1 ? i : i + 1; i < n; i += 2)
		if (s[i]) p.push_back(i);
}

long pollard_cycle(long n, int c)
{
    long x = 2, y = 2, d = 1;
    while (d == 1) {
        x = (x*x + c) % n;
        y = (y*y + c) % n;
        y = (y*y + c) % n;
        d = gcd(labs(x-y), n);
    }
    return d;
}

/* Pollard's rho method
 *  - assert n > 0           */
map<long,long> pollard_factor(long n)
{
    map<long,long> fact;

    for ( ; n % 2 == 0; n /= 2)            // purge evenness first
        fact[2] += 1;

    long d;
    for ( ; n > 1; n /= d)
    {
        for (int c = -4; c <= 4; c++)
        {
            if (c == 0 || c == -2)          // x^2, x^2-2 do not converge
                continue;
            if ( n != (d = pollard_cycle(n, c)) )
                break;
        }

        fact[d] += 1;
    }
    return fact;
}

bool isSquare(long n)
{
    if ( (n & 2) || (n & 7) == 5 || (n & 11) == 8 )
        return false;
    int t = (int) round( sqrt((double) n) );
    return t*t == n;
}

/* Newton's factorization method
 *  - breaks if n is even            */
//TODO
/*
map<long,long> newton_factor(long n)
{
    map<long,long> fact;
    
    for (int a = ceil(sqrt(n)) + 1; ; a++)
    {
        if (isSquare(a * a - N))
        {
        }
    }
    return fact;
}
*/

//** NOT TESTED
/* Euler's totient function */
long nt_phi(long n)
{
    long t = 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        while (i->second > 0)
        {
            t *= i->second > 1 ? i->first : i->first - 1;
            i->second --;
        }
    return t;
}

//** NOT TESTED
/* Mobius function */
long nt_mu(long n)
{
    if (n == 1) return 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        if (i->second >= 2)
            return 0;

    return f.size() % 2 == 0 ? 1 : -1;
}

//** NOT TESTED
/* Number of divisors function */
long nt_d(long n)
{
    int t = 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        t *= i->second + 1;
    return t;
}

//** NOT TESTED
/* Generalized sum of divisors function */
long nt_sigma_k(long n, int k)
{
    int t = 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        t *= (ipow(i->first, k * (i->second + 1) ) - 1)
			/ (ipow(i->first, k) - 1);
    return t;
}

/* Catalan numbers
 * 1, 1, 2, 5, 14, 42, 132, 429, etc
 */
//** NOT TESTED
typedef long long big;
vector<big> cat;
big catalan(int n)
{
    while (cat.size() <= n)
    {
        if (cat.size() == 0)
            cat.push_back(1LL);
        big s = 0LL;
        for (int i = 0; i < cat.size(); i++)
            s += cat[i] * cat[cat.size()-i-1];
        cat.push_back(s);
    }
    return cat[n];
}
