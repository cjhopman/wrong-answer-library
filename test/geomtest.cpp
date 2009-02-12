#include "../geometry-dhe.cpp"

#include <iostream>
#include <cassert>
#include <cmath>
#define ASSERT(x) assert((x))
#define approx(a, b) assert( abs(a-b) < EPS)
#define equal(a, b) assert( a == b )
#define ptinvalid(a) assert( isnan(imag(a)) || isnan(real(a)) || isinf(imag(a)) || isinf(real(a)) )

int main()
{
    /* distPtLine */
    approx( distPtLine( pt( 0.0, 0.0), pt( 1.0, 0.0), pt( 0.0, 1.0) ) , sqrt(2)/2 );
    approx( distPtLine( pt( 0.0, 0.0), pt( 3.0, 0.0), pt( 0.0, 4.0) ) , 3.0*4.0/5.0 );
    // edge cases
    approx( distPtLine( pt( 0.0, 0.0), pt( 1.0, 0.0), pt(-1.0, 0.0) ) , 0 );
    approx( distPtLine( pt( 0.0, 0.0), pt( 0.0, 0.0), pt( 1.0, 0.0) ) , 0 );
    assert( isnan( distPtLine( pt( 0.0, 0.0), pt( 1.0, 0.0), pt( 1.0, 0.0) ) ) );
    assert( isnan( distPtLine( pt( 0.0, 0.0), pt( 0.0, 0.0), pt( 0.0, 0.0) ) ) );

    /* distPtSeg */
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 0.0), pt( 0.0, 1.0) ) , sqrt(2)/2 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 1.0), pt( 2.0, 1.0) ) , sqrt(2) );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 0.0), pt( 0.5, 0.0) ) , 0.5 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 0.0, 1.0), pt( 1.0, 1.0) ) , 1.0 );
    approx( distPtSeg( pt( 0.0, 0.0), pt(-1.0, 1.0), pt( 1.0, 1.0) ) , 1.0 );
    // edge cases
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 0.0), pt(-1.0, 0.0) ) , 0.0 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 0.0, 1.0), pt( 0.0, 0.0) ) , 0.0 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 0.0), pt( 0.0, 0.0) ) , 0.0 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 0.0, 0.0), pt( 0.0, 0.0) ) , 0.0 );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 1.0, 1.0), pt( 1.0, 1.0) ) , sqrt(2) );
    approx( distPtSeg( pt( 0.0, 0.0), pt( 0.0, 0.0), pt( 0.0, 0.0) ) , 0.0 );

    /* xSegSeg */
    assert(xSegSeg( pt(0.0,0.0), pt(1.0,1.0),  pt(0.0,1.0), pt(1.0,0.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(3.0,1.0),  pt(2.0,1.0), pt(9.0,2.0) ) == 0);
    assert(xSegSeg( pt(0.0,0.0), pt(3.0,1.0),  pt(3.0,1.0), pt(9.0,2.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(3.0,2.0),  pt(2.0,1.0), pt(9.0,2.0) ) == 0);
    assert(xSegSeg( pt(0.0,0.0), pt(100.0,0.0),  pt(0.0,1.0), pt(100.0,-1.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(100.0,0.0),  pt(0.0,1.0), pt(100.0, 1.0) ) == 0);
    // edge cases
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,1.0),  pt(0.0,1.0), pt(0.0,2.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,1.0),  pt(0.0,1.0), pt(1.0,1.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,2.0),  pt(0.0,1.0), pt(0.0,3.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,2.0),  pt(0.0,1.0), pt(1.0,1.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,1.0),  pt(0.0,0.0), pt(0.0,1.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,3.0),  pt(0.0,2.0), pt(0.0,1.0) ) == 1);
    assert(xSegSeg( pt(0.0,0.0), pt(0.0,0.0),  pt(0.0,0.0), pt(0.0,0.0) ) == 1);

    /* xLineLine */
    approx( xLineLine( pt(0.0,0.0), pt(1.0,1.0),  pt(1.0,0.0), pt(0.0,1.0) ) , pt(0.5,0.5) );
    approx( xLineLine( pt(0.0,0.0), pt(1.0,0.0),  pt(1.0,0.0), pt(1.0,1.0) ) , pt(1.0,0.0) );
    approx( xLineLine( pt(2.0,2.0), pt(8.0,8.0),  pt(3.0,4.0), pt(7.0,6.0) ) , pt(5.0,5.0) );
    // edge cases
    ptinvalid( xLineLine( pt(0.0,0.0), pt(5.0,0.0),  pt(0.0,1.0), pt(5.0,1.0) ) );
    ptinvalid( xLineLine( pt(0.0,0.0), pt(5.0,0.0),  pt(5.0,0.0), pt(7.0,0.0) ) );
    ptinvalid( xLineLine( pt(0.0,0.0), pt(0.0,5.0),  pt(1.0,0.0), pt(1.0,5.0) ) );
    ptinvalid( xLineLine( pt(0.0,0.0), pt(0.0,6.0),  pt(1.0,0.0), pt(1.0,5.0) ) );
    ptinvalid( xLineLine( pt(0.0,0.0), pt(0.0,0.0),  pt(5.0,0.0), pt(7.0,0.0) ) );
    ptinvalid( xLineLine( pt(0.0,0.0), pt(0.0,0.0),  pt(0.0,0.0), pt(0.0,0.0) ) );
    return 0;
}


