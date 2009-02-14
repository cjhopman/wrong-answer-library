
#include <valarray>

typedef valarray<int> perm;

perm perm_identity(int n)
{
    perm r;
    for (int i = 0; i < n; i++)
        r[i] = i;
    return r;
}

perm perm_compose(perm &a, perm &b)
{
    perm r;
    for (int i = 0; i < n; i++)
        r[i] = a[b[i]];
    return r;
}

perm perm_invert(perm &a)
{
    perm r;
    for (int i = 0; i < n; i++)
        r[a[i]] = i;
    return r;
}


