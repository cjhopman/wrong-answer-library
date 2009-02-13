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
long nt_mu(long n)
{
    if (n == 1)
        return 1;

    map<long,long> f = trial_factor(n);
    
    for (map<long,long>::iterator i = f.begin(); i != f.end(); i++)
        if (i->second == 2)
            return 0;

    return f.size() % 2 == 0 ? 1 : -1;
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
