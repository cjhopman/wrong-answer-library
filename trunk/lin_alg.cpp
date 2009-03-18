//Linear algebra stuff goes here
//Stuff to add:
//  Matrix multiplication
//	Vector arithmetic
//	LU decomposition
//		Inverse
//		Determinant
//	QR factorization
//		Eigenvector solver
//

#include <valarray>
#include <complex>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int,int>           pii;
typedef complex<long double>    field;
typedef valarray<field>         vec;
typedef valarray<vec>           mat;

#define DIMS(m)     pii((m).size(),(m)[0].size())

//Matrix constructor
//NOT TESTED
mat zeros(pii d)
{
    return mat(vec(0., d.first), d.second);
}

//Creates an identity matrix
//NOT TESTED
mat identity(int n)
{
    mat r = zeros(pii(n, n));
    for(int i=0; i<n; i++)
        r[i][i] = 1.;
    return r;
}

//Transposes the matrix
//NOT TESTED
mat transpose(const mat& m)
{
    pii d = DIMS(m);
    mat r = zeros(d);
    for(int i=0; i<d.first; i++)
    for(int j=0; j<d.second; j++)
        r[i][j] = m[j][i];
    return r;
}

//Matrix product
//NOT TESTED
mat operator*(const mat& a, const mat& b)
{
    pii da = DIMS(a), db = DIMS(b);
    mat r = zeros(pii(da.first, db.second));
    for(int i=0; i<da.first; i++)
    for(int j=0; j<db.second; j++)
        r[i][j] = (a[i] * b[j]).sum();
    return r;
}

//LU decomposition
//NOT IMPLEMENTED
mat lu_decomp(const mat& m)
{
    return m;
}


//Determinant
//NOT TESTED
field det(const mat& m)
{
    pii d = DIMS(m);
    mat lu = lu_decomp(m);
    field r = 1.0;
    for(int i=0; i<min(d.first, d.second); i++)
        r *= lu[i][i];
    return r;
}





//Test code

int main(int argc, char ** argv)
{
    return 0;
}
