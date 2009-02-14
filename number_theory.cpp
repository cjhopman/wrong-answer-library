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
#include <cstdlib>  // labs
#include <stdint.h>

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

/* finds all primes up to and including n */
#define SIEVE_E1_GET(i) ( P[(i)/64]  & 1L << (i)%64 )
#define SIEVE_E1_SET(i) ( P[(i)/64] |= 1L << (i)%64 )
void sieve_eratosthenes(long n, vector<long> &pout)
{
    uint64_t *P = new uint64_t[n/64+1];
    fill_n(P, n/64+1, 0);

    for (long i = 2; i <= n; i++)
        if (SIEVE_E1_GET(i) == 0) {
            for (long k = 2; k*i <= n; k++)
                SIEVE_E1_SET(k*i);
            pout.push_back(i);
        }

    delete[] P;
}

/* same as first sieve, except 
 *  - only consider odd numbers           
 *  - stop at sqrt(n)                    
 *  - cross out less numbers            
 *      ( fails if n < 2 )                */
#define SIEVE_E2_GET(i) ( P[(i)/128]  & 1L << (i)/2%64 )
#define SIEVE_E2_SET(i) ( P[(i)/128] |= 1L << (i)/2%64 )
void sieve_eratosthenes_2(long n, vector<long> &pout)
{
    uint64_t *P = new uint64_t[n/128+1];
    fill_n(P, n/128+1, 0);

    pout.push_back(2);

    long i;
    for (i = 3; i*i <= n; i += 2)
        if (SIEVE_E2_GET(i) == 0) {
            for (long k = i; k*i <= n; k += 2)
                SIEVE_E2_SET(k*i);
            pout.push_back(i);
        }

    for ( ; i <= n; i+= 2)
        if (SIEVE_E2_GET(i) == 0)
            pout.push_back(i);

    delete[] P;
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
 *  - breaks if n == 0           */
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
