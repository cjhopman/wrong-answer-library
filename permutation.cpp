
#include <valarray>
#include <cstdlib>   //rand()

#define swap(a,b) {int _t = a; a = b; b = _t; }

typedef valarray<int> perm;

// NOT TESTED
perm perm_identity(int n)
{
    perm r(n);
    for (int i = 0; i < n; i++)
        r[i] = i;
    return r;
}

// NOT TESTED
perm perm_compose(perm &a, perm &b)
{
    perm r(a.size());
    for (int i = 0; i < r.size(); i++)
        r[i] = a[b[i]];
    return r;
}

// NOT TESTED
perm perm_invert(perm &p)
{
    perm r(p.size());
    for (int i = 0; i < r.size(); i++)
        r[p[i]] = i;
    return r;
}

/* In place random shuffle using Fisher-Yates ( O(n) varient )
 *   - randomness guaranteed only when rng is good!
 *   - overrides p !                                     */
// NOT TESTED
void perm_shuffle(perm &p)
{
    for (int n = p.size(); n > 1; n--)
    {
        int k = rand() % n;
        swap(p[n-1], p[k]);
    }
}

/* In place random cyclic shuffle using Sattolo's algorithm
 *   - randomness guaranteed only when rng is good!
 *   - overrides p !                                     */
// NOT TESTED
void perm_cyclic_shuffle(perm &p)
{
    for (int n = p.size(); n > 1; n--)
    {
        int k = rand() % (n-1);
        swap(p[n-1], p[k]);
    }
}

/* I'm not sure how this works, but given 0 <= k < n!, 
 * this generates a unique permutation. */
// NOT TESTED
perm perm_gen1(int k, int n)
{ 
    perm r(n);
    for (int j = 2; j <= n; j++) {
        k /= (j-1); 
        swap(s[(k % j) + 1], s[j]); 
    }
    return r;
}

/* Given 0 <= k < n!, 
 * this generates the kth lexicographical permutation. */
// NOT TESTED
// TODO
perm perm_gen2(int k, int n)
{ 
    perm r(n);
    return r;
}


/* Calculates the inversion sequence */
// NOT TESTED
valarray<int> perm_invseq(perm &p)
{
    valarray<int> r;
}


