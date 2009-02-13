#include "../geometry-dhe.cpp"

#include <iostream>
#include <cassert>
#include <cmath>
#define ASSERT(x) assert((x))
#define approx(a, b) assert( abs(a-b) < EPS)
#define equal(a, b) assert( a == b )
#define ptinvalid(a) assert( isnan(imag(a)) || isnan(real(a)) || isinf(imag(a)) || isinf(real(a)) )

void distPtLine_test()
{
    approx( distPtLine( pt( 0, 0), pt( 1, 0), pt( 0, 1) ) , sqrt(2)/2 );
    approx( distPtLine( pt( 0, 0), pt( 3, 0), pt( 0, 4) ) , 3.0*4.0/5.0 );
    // edge cases
    approx( distPtLine( pt( 0, 0), pt( 1, 0), pt(-1, 0) ) , 0 );
    // corner cases
    approx( distPtLine( pt( 0, 0), pt( 0, 0), pt( 1, 0) ) , 0 );
    assert( isnan( distPtLine( pt( 0, 0), pt( 1, 0), pt( 1, 0) ) ) );
    assert( isnan( distPtLine( pt( 0, 0), pt( 0, 0), pt( 0, 0) ) ) );
}

void distPtSeg_test()
{
    approx( distPtSeg( pt( 0, 0), pt( 1, 0), pt( 0, 1) ) , sqrt(2)/2 );
    approx( distPtSeg( pt( 0, 0), pt( 1, 1), pt( 2, 1) ) , sqrt(2) );
    approx( distPtSeg( pt( 0, 0), pt( 1, 0), pt( 0.5, 0) ) , 0.5 );
    approx( distPtSeg( pt( 0, 0), pt( 0, 1), pt( 1, 1) ) , 1 );
    approx( distPtSeg( pt( 0, 0), pt(-1, 1), pt( 1, 1) ) , 1 );
    // edge cases
    approx( distPtSeg( pt( 0, 0), pt( 1, 0), pt(-1, 0) ) , 0 );
    // corner cases
    approx( distPtSeg( pt( 0, 0), pt( 0, 1), pt( 0, 0) ) , 0 );
    approx( distPtSeg( pt( 0, 0), pt( 1, 0), pt( 0, 0) ) , 0 );
    approx( distPtSeg( pt( 0, 0), pt( 0, 0), pt( 0, 0) ) , 0 );
    approx( distPtSeg( pt( 0, 0), pt( 1, 1), pt( 1, 1) ) , sqrt(2) );
    approx( distPtSeg( pt( 0, 0), pt( 0, 0), pt( 0, 0) ) , 0 );
}

void xSegSeg_test()
{
    /* closed version */
    assert( xSegSeg( pt(0,0), pt(1,1),  pt(0,1), pt(1,0) ) );
    assert(!xSegSeg( pt(0,0), pt(3,1),  pt(2,1), pt(9,2) ) );
    assert(!xSegSeg( pt(0,0), pt(3,2),  pt(2,1), pt(9,2) ) );
    assert( xSegSeg( pt(0,0), pt(100,0),  pt(0,1), pt(100,-1) ) );
    assert(!xSegSeg( pt(0,0), pt(100,0),  pt(0,1), pt(100, 1) ) );
    assert( xSegSeg( pt(0,0), pt(2,8),  pt(1,6), pt(8,3) ) );
    // edge-corner cases
    {
        pt a(0,0), b(2,0), c(1,0), d(1,3);
        assert( xSegSeg( a,b, c,d) );
        assert( xSegSeg( a,b, d,c) );
        assert( xSegSeg( b,a, c,d) );
        assert( xSegSeg( b,a, d,c) );
    }
    // edge-edge cases
    assert( xSegSeg( pt(0,0), pt(0,2),  pt(0,1), pt(0,3) ) );
    {
        pt a(0,0), b(0,1), c(0,2), d(0,3);
        assert( xSegSeg( a,d, b,c) );
        assert( xSegSeg( a,d, c,b) );
        assert( xSegSeg( d,a, b,c) );
        assert( xSegSeg( d,a, c,b) );
        assert(!xSegSeg( a,b, c,d) );
        assert(!xSegSeg( b,a, c,d) );
        assert(!xSegSeg( a,b, d,c) );
        assert(!xSegSeg( b,a, d,c) );
    }
    assert(!xSegSeg( pt(3,6), pt(4,8),  pt(1,2), pt(2,4) ) );
    // corner-corner cases
    assert( xSegSeg( pt(0,0), pt(3,1),  pt(3,1), pt(9,2) ) );
    assert( xSegSeg( pt(0,0), pt(0,1),  pt(0,1), pt(0,2) ) );
    assert( xSegSeg( pt(0,0), pt(0,1),  pt(0,1), pt(1,1) ) );
    assert( xSegSeg( pt(0,0), pt(0,1),  pt(0,0), pt(0,1) ) );
    assert( xSegSeg( pt(0,0), pt(0,0),  pt(0,0), pt(0,0) ) );
    
    /* open version */
    assert( xSegSeg_open( pt(0,0), pt(1,1),  pt(0,1), pt(1,0) ) );
    assert(!xSegSeg_open( pt(0,0), pt(3,1),  pt(2,1), pt(9,2) ) );
    assert(!xSegSeg_open( pt(0,0), pt(3,2),  pt(2,1), pt(9,2) ) );
    assert( xSegSeg_open( pt(0,0), pt(100,0),  pt(0,1), pt(100,-1) ) );
    assert(!xSegSeg_open( pt(0,0), pt(100,0),  pt(0,1), pt(100, 1) ) );
    assert( xSegSeg_open( pt(0,0), pt(2,8),  pt(1,6), pt(8,3) ) );
    // edge-corner cases
    {
        pt a(0,0), b(2,0), c(1,0), d(1,3);
        assert(!xSegSeg_open( a,b, c,d) );
        assert(!xSegSeg_open( a,b, d,c) );
        assert(!xSegSeg_open( b,a, c,d) );
        assert(!xSegSeg_open( b,a, d,c) );
    }
    // edge-edge cases
    assert(!xSegSeg_open( pt(0,0), pt(0,2),  pt(0,1), pt(0,3) ) );
    {
        pt a(0,0), b(0,1), c(0,2), d(0,3);
        assert(!xSegSeg_open( a,d, b,c) );
        assert(!xSegSeg_open( a,d, c,b) );
        assert(!xSegSeg_open( d,a, b,c) );
        assert(!xSegSeg_open( d,a, c,b) );
        assert(!xSegSeg_open( a,b, c,d) );
        assert(!xSegSeg_open( b,a, c,d) );
        assert(!xSegSeg_open( a,b, d,c) );
        assert(!xSegSeg_open( b,a, d,c) );
    }
    assert(!xSegSeg_open( pt(3,6), pt(4,8),  pt(1,2), pt(2,4) ) );
    // corner-corner cases
    assert(!xSegSeg_open( pt(0,0), pt(3,1),  pt(3,1), pt(9,2) ) );
    assert(!xSegSeg_open( pt(0,0), pt(0,1),  pt(0,1), pt(0,2) ) );
    assert(!xSegSeg_open( pt(0,0), pt(0,1),  pt(0,1), pt(1,1) ) );
    assert(!xSegSeg_open( pt(0,0), pt(0,1),  pt(0,0), pt(0,1) ) );
    assert(!xSegSeg_open( pt(0,0), pt(0,0),  pt(0,0), pt(0,0) ) );
}

void xLineLine_test()
{
    approx( xLineLine( pt(0,0), pt(1,1),  pt(1,0), pt(0,1) ) , pt(0.5,0.5) );
    approx( xLineLine( pt(0,0), pt(1,0),  pt(1,0), pt(1,1) ) , pt(1,0) );
    approx( xLineLine( pt(2,2), pt(8,8),  pt(3,4), pt(7,6) ) , pt(5,5) );
    // edge cases
    ptinvalid( xLineLine( pt(0,0), pt(5,0),  pt(0,1), pt(5,1) ) );
    ptinvalid( xLineLine( pt(0,0), pt(5,0),  pt(6,0), pt(7,0) ) );
    ptinvalid( xLineLine( pt(0,0), pt(5,0),  pt(6,1), pt(7,1) ) );
    ptinvalid( xLineLine( pt(0,0), pt(0,5),  pt(1,0), pt(1,5) ) );
    ptinvalid( xLineLine( pt(0,0), pt(0,6),  pt(1,0), pt(1,5) ) );
    // corner cases
    ptinvalid( xLineLine( pt(0,0), pt(5,0),  pt(5,0), pt(7,0) ) );
    ptinvalid( xLineLine( pt(0,0), pt(0,0),  pt(5,0), pt(7,0) ) );
    ptinvalid( xLineLine( pt(0,0), pt(0,0),  pt(0,0), pt(0,0) ) );
}

void in_triangle_test()
{
    /* closed version */
    assert( in_triangle( pt(1,1),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle( pt(2,2),   pt(0,0), pt(0,3), pt(4,0) ));
    assert( in_triangle( pt(1,2),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle( pt(0,6),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle( pt(6,0),   pt(0,0), pt(0,3), pt(4,0) ));
    // edge cases
    assert( in_triangle( pt(2,0),   pt(0,0), pt(0,3), pt(4,0) ));
    assert( in_triangle( pt(3,0),   pt(0,0), pt(0,3), pt(4,0) ));
    // corner cases
    assert( in_triangle( pt(0,0),   pt(0,0), pt(0,3), pt(4,0) ));
    assert( in_triangle( pt(0,3),   pt(0,0), pt(0,3), pt(4,0) ));
    assert( in_triangle( pt(4,0),   pt(0,0), pt(0,3), pt(4,0) ));

    /* open version */
    assert( in_triangle_open( pt(1,1),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(2,2),   pt(0,0), pt(0,3), pt(4,0) ));
    assert( in_triangle_open( pt(1,2),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(0,6),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(6,0),   pt(0,0), pt(0,3), pt(4,0) ));
    // edge cases
    assert(!in_triangle_open( pt(2,0),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(3,0),   pt(0,0), pt(0,3), pt(4,0) ));
    // corner cases
    assert(!in_triangle_open( pt(0,0),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(0,3),   pt(0,0), pt(0,3), pt(4,0) ));
    assert(!in_triangle_open( pt(4,0),   pt(0,0), pt(0,3), pt(4,0) ));
}

void isParallel_test()
{
    assert(!isParallel( pt(0,0), pt(1,1),   pt(0,1), pt(1,0) ));
    assert( isParallel( pt(0,0), pt(1,1),   pt(0,1), pt(1,2) ));
    assert(!isParallel( pt(3,5), pt(8,2),   pt(1,1), pt(7,6) ));
    assert( isParallel( pt(3,5), pt(8,2),   pt(1,3), pt(6,0) ));
    assert(!isParallel( pt(4,8), pt(8,9),   pt(2,7), pt(5,8) ));
    assert( isParallel( pt(4,8), pt(8,9),   pt(2,7), pt(6,8) ));
    assert(!isParallel( pt(0,1), pt(0,2),   pt(0,0), pt(1,0) ));
    assert( isParallel( pt(0,1), pt(0,2),   pt(1,1), pt(1,0) ));
    // edge cases
    assert( isParallel( pt(0,0), pt(3,0),   pt(0,0), pt(5,0) ));
    assert( isParallel( pt(0,0), pt(3,0),   pt(1,0), pt(5,0) ));
    assert( isParallel( pt(0,0), pt(3,0),   pt(3,0), pt(5,0) ));
    assert( isParallel( pt(0,0), pt(1,0),   pt(4,0), pt(5,0) ));
    assert( isParallel( pt(0,0), pt(3,0),   pt(0,0), pt(3,0) ));
    assert( isParallel( pt(1,2), pt(2,4),   pt(3,6), pt(4,8) ));
    assert( isParallel( pt(1,2), pt(4,8),   pt(2,4), pt(3,6) ));
    // corner cases
    assert( isParallel( pt(0,0), pt(0,0),   pt(0,1), pt(0,2) ));
    assert( isParallel( pt(0,0), pt(0,0),   pt(0,3), pt(0,2) ));
    assert( isParallel( pt(0,0), pt(0,0),   pt(1,3), pt(1,2) ));
    assert( isParallel( pt(0,0), pt(0,0),   pt(1,1), pt(1,1) ));
    assert( isParallel( pt(0,0), pt(0,0),   pt(0,0), pt(0,0) ));
}

void xPtSeg_test()
{
    assert( xPtSeg( pt(3,3),  pt(2,2), pt(4,4) ));
    assert(!xPtSeg( pt(3,3),  pt(2,3), pt(4,4) ));
    assert( xPtSeg( pt(3,3),  pt(2,3), pt(4,3) ));
    assert( xPtSeg( pt(3,3),  pt(0,3), pt(9,3) ));
    assert(!xPtSeg( pt(3,4),  pt(3,3), pt(2,3) ));
    assert(!xPtSeg( pt(3,4),  pt(2,3), pt(3,3) ));
    assert(!xPtSeg( pt(3,3),  pt(2,2), pt(1,1) ));
    assert(!xPtSeg( pt(3,6),  pt(1,2), pt(2,4) ));
    // corner cases
    assert( xPtSeg( pt(3,3),  pt(3,3), pt(4,4) ));
    assert( xPtSeg( pt(3,3),  pt(3,3), pt(3,4) ));
    assert( xPtSeg( pt(3,3),  pt(3,3), pt(4,3) ));
    assert( xPtSeg( pt(3,3),  pt(4,4), pt(3,3) ));
    assert( xPtSeg( pt(3,3),  pt(3,3), pt(3,3) ));
}

int main (int argc, char **argv)
{
    distPtLine_test();
    distPtSeg_test();
    xSegSeg_test();
    xLineLine_test();
    isParallel_test();
    xPtSeg_test();
    in_triangle_test();
    return 0;
}


