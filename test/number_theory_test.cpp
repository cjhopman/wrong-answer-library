#include "../number_theory.cpp"

#include <iostream>
#include <cassert>
#include <cmath>

#include <vector>

void factor_test()
{
    map<long,long> f;

    f = trial_factor(10);
    assert(
        f.size() == 2 &&
        f[2] == 1     &&
        f[5] == 1        );

    f = trial_factor(24);
    assert(
        f.size() == 2 &&
        f[2] == 3     &&
        f[3] == 1        );

    f = trial_factor(4096);
    assert(
        f.size() == 1 &&
        f[2] == 12       );

    f = trial_factor(120);
    assert(
        f.size() == 3 &&
        f[2] == 3     &&
        f[3] == 1     &&
        f[5] == 1        );

    f = trial_factor(2L*2*3*13*13*17*17*17);
    assert(
        f.size() == 4 &&
        f[ 2] == 2    &&
        f[ 3] == 1    &&
        f[13] == 2    &&
        f[17] == 3       );

    f = trial_factor(4414);
    assert(
        f.size() == 2 &&
        f[   2]  == 1 &&
        f[2207]  == 1    );

    f = trial_factor(99623L*99643L);
    assert(
        f.size() == 2 &&
        f[99623] == 1 &&
        f[99643] == 1    );

    f = trial_factor(2);
    assert(
        f.size() == 1 &&
        f[    2] == 1    );

    f = trial_factor(101);
    assert(
        f.size() == 1 &&
        f[  101] == 1    );

    f = trial_factor(65537);
    assert(
        f.size() == 1 &&
        f[65537] == 1    );

    f = trial_factor(1);
    assert( f.size() == 0 );

    f = trial_factor(0);
    assert( f.size() == 0 );
}

void multiplicative_function_test()
{

}

void sieve_test()
{
    typedef void (*sieve_t)(long, vector<long> &);
    sieve_t sieve_fns[] = 
    {
        &sieve_eratosthenes,
        &sieve_eratosthenes_2,
    } ;

    for (int i = 0; i < 2; i++)
    {
        vector<long> p;
        sieve_t fp = sieve_fns[i];

        p.clear();
        fp(100000000, p);
        assert(p.size() == 5761455);

        p.clear();
        fp(65537, p);
        assert(p.size() == 6543);

        p.clear();
        fp(150, p);
        assert(p.size() == 35);

        p.clear();
        fp(10, p);
        assert(p.size() == 4);

        p.clear();
        fp(7, p);
        assert(p.size() == 4);

        p.clear();
        fp(3, p);
        assert(p.size() == 2);

        p.clear();
        fp(2, p);
        assert(p.size() == 1);
    }
}

int main (int argc, char **argv)
{
    factor_test();
    multiplicative_function_test();
    sieve_test();
    return 0;
}


