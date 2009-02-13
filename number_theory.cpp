//Misc. number theory code goes here
// Stuff to add:
//	Prime factorization
//	Divisor function
//	Totient
//	Seive
//	GCD
//	LCM
//	Extended euclidean algorithm
//	Pell's equation

#include <cmath>
#include <map>
#include <vector>

using namespace std;

//** NOT TESTED
long gcd(long a, long b)
{
    while (b != 0)
    { long t=b; b = a%b; a=t; }
    return a;
}

long lcm(long a, long b) { return a / gcd(a, b) * b; }

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

//** NOT TESTED
pair<int,int> extended_gcd(long a, long b)
{
    if (a % b == 0)
        return pair<int,int>(0, 1);
    else {
        pair<int,int> t = extended_gcd(b, a % b);
        return pair<int,int>(t.second, t.first-t.second*(a/b));
    }
}

//** NOT TESTED
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
/* Mobieus function */
long nt_mu(long n)
{
    if (n == 1) return 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        if (i->second == 2)
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
/* Sum of divisors function */
long nt_sigma(long n)
{
    int t = 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        t *= (ipow(i->first, i->second + 1) - 1) / (i->first - 1);
    return t;
}

//** NOT TESTED
/* Generalized sum of divisors function */
long nt_sigma_k(long n, int k)
{
    int t = 1;
    map<long,long> f = trial_factor(n);
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        t *= (ipow(i->first, k * (i->second + 1) ) - 1) / (ipow(i->first, k) - 1);
    return t;
}

// integer square root
//** NOT TESTED
int isqrt(double n)
{
    double s, t = 0;
    for (s = n; abs(t-s) > 0.5; s = t)
        t = 0.5 * (s + n / s);
    return floor(s);
}
