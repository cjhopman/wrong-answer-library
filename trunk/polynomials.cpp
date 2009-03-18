//Polynomial srithmetic stuff
//	Polynomial class
//		Addition
//		Multiplication
//		Division
//	Calculus
//		Derivative
//		Integral
//
// Stuff to add:
//
//	Root finding
//		Newton's method
//		Weierstrass
//	Algebra stuff
//		Resultant (checks for common zeros)
// 	Change of basis
//		Grobner
//		Dirac


#include <iostream>
#include <valarray>
#include <algorithm>
#include <complex>
#include <cassert>
#include <vector>

using namespace std;

#define EPS     1e-8

//Polynomial types
typedef complex<long double>   field;
typedef valarray<field>        poly;


//Debug output
ostream& operator<<(ostream& os, const poly& a)
{
    for(int i=a.size()-1; i>=0; i--)
    {   os << a[i];
        if(i > 0)
            os << "x^" << i << "+";
    }
    return os;
}


//Polynomial multiplication (not optimal)
poly operator*(const poly& a, const poly& b)
{
    poly r(0., a.size() + b.size() - 1);
    for(int i=0; i<b.size(); i++)
        r[slice(i, a.size()+i-1, 1)] += a * b[i];
    return r;
}

//Evaluate a polynomial
field eval(const poly& p, const field& x)
{
    field r = 0., v=1.;
    for(int i=0; i<p.size(); i++, v*=x)
        r += p[i] * v;
    return r;
}

//Computes the degree of p
int deg(const poly& p)
{
    int d = p.size();
    while(d > 0 && abs(p[--d]) <= EPS) { }
    return d;
}

//Computes the degree of p
poly trim(const poly& p)
{
    if(p.size() == 0)
        return p;
    return p[slice(0, deg(p)+1, 1)];
}

//Polynomial division, returns quotient and remainder
pair<poly,poly> div(const poly& a, const poly& b)
{
    poly D = trim(b);
    assert(D.size() > 0);
    
    poly rem = trim(a);
    if(D.size() > rem.size())
        return make_pair(poly(0), rem);

    poly quot = poly(deg(a) - deg(D)+1);
    field v = D[D.size()-1];
    
    for(int i=rem.size()-D.size(); i>=0; i--)
    {
        quot[i] = rem[i + D.size()-1] / v;
        rem[slice(i, i+D.size()-1, 1)] -= quot[i] * D;
    }
    return make_pair(trim(quot), trim(rem));
}


//Computes a derivative of a polynomial
poly deriv(const poly& p)
{
    if(p.size() == 0) return p;
    poly r(p.size()-1);
    for(int i=0; i<r.size(); i++)
        r[i] = p[i+1] * field(i+1);
    return r;
}


//Computes the path integral from a to b
//NOT TESTED
field integral(const poly& p, field a, field b)
{
    field sa = 0., sb = 0., xa = a, xb = b;
    for(int i=0; i<p.size(); i++, xa *= a, xb *= b)
    {
        sa += xa * p[i] / field(i+1);
        sb += xb * p[i] / field(i+1);
    }
    return sb - sa;
}

//Converts a degree sequence to a polynomial
poly seq_to_poly(const poly& s)
{
}


//Newton's method for finding a root
field newton_root(const poly& p, field x0)
{
    return x0;
}

//Weierstrauss' method for finding all roots of a polynomial (in parallel)
poly weierstrauss_root(const poly& p)
{
}



//Test code starts here



int main(int argc, char ** argv)
{
    poly a(3), b(2), c(4), q, r;
    
    c[0] = 1;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    
    a[0] = 1.;
    a[1] = 0.;
    a[2] = 2.;
    
    b[0] = 3.;
    b[1] = 5.;
    
    pair<poly,poly> res = div(a * b, b);
    
    cout 
         << "A(1) = " << eval(a, 1) << endl
         << "trim(C) = " << trim(c) << endl
         << "A = " << a << endl
         << "B = " << b << endl
         << "A*B = " << (a * b) << endl
         << "A/B = " << res.first << endl
         << "A%B = " << res.second << endl
         << "A' = " << deriv(a) << endl;
    
    
    
    return 0;
}
