#include "../geom_prim.cpp"

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
    typedef bool (*xsegseg_t)(pt, pt, pt, pt);
    xsegseg_t xsegseg_fns[] = 
    {
        &xSegSeg,
        &xSegSeg_open,
        &xSegSeg_simple
    } ;

    for (int i = 0; i < 3; i++)
    {
        xsegseg_t fp = xsegseg_fns[i];

        assert( fp( pt(0,0), pt(1,1),  pt(0,1), pt(1,0) ) );
        assert(!fp( pt(0,0), pt(3,1),  pt(2,1), pt(9,2) ) );
        assert(!fp( pt(0,0), pt(3,2),  pt(2,1), pt(9,2) ) );
        assert( fp( pt(0,0), pt(100,0),  pt(0,1), pt(100,-1) ) );
        assert(!fp( pt(0,0), pt(100,0),  pt(0,1), pt(100, 1) ) );
        assert( fp( pt(0,0), pt(2,8),  pt(1,6), pt(8,3) ) );
        
        if (fp == &xSegSeg_simple) continue;

        // edge-corner cases
        {
            pt a(0,0), b(2,0), c(1,0), d(1,3);
            assert( fp( a,b, c,d) == (fp == &xSegSeg) );
            assert( fp( a,b, d,c) == (fp == &xSegSeg) );
            assert( fp( b,a, c,d) == (fp == &xSegSeg) );
            assert( fp( b,a, d,c) == (fp == &xSegSeg) );
        }
        // edge-edge cases
        assert( fp( pt(0,0), pt(0,2),  pt(0,1), pt(0,3) ) == (fp == &xSegSeg) );
        {
            pt a(0,0), b(0,1), c(0,2), d(0,3);
            assert( fp( a,d, b,c) == (fp == &xSegSeg) );
            assert( fp( a,d, c,b) == (fp == &xSegSeg) );
            assert( fp( d,a, b,c) == (fp == &xSegSeg) );
            assert( fp( d,a, c,b) == (fp == &xSegSeg) );
            assert(!fp( a,b, c,d) );
            assert(!fp( b,a, c,d) );
            assert(!fp( a,b, d,c) );
            assert(!fp( b,a, d,c) );
        }
        assert(!fp( pt(3,6), pt(4,8),  pt(1,2), pt(2,4) ) );
        // corner-corner cases
        assert( fp( pt(0,0), pt(3,1),  pt(3,1), pt(9,2) ) == (fp == &xSegSeg) );
        assert( fp( pt(0,0), pt(0,1),  pt(0,1), pt(0,2) ) == (fp == &xSegSeg) );
        assert( fp( pt(0,0), pt(0,1),  pt(0,1), pt(1,1) ) == (fp == &xSegSeg) );
        assert( fp( pt(0,0), pt(0,1),  pt(0,0), pt(0,1) ) == (fp == &xSegSeg) );
        assert(!fp( pt(0,0), pt(0,0),  pt(1,1), pt(2,1) ) );
        assert(!fp( pt(0,0), pt(0,0),  pt(1,1), pt(1,1) ) );
        assert( fp( pt(0,0), pt(0,0),  pt(0,0), pt(0,0) ) == (fp == &xSegSeg) );
    }
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
    typedef bool (*in_triangle_t)(pt, pt, pt, pt);
    in_triangle_t in_triangle_fns[] = 
    {
        &in_triangle,
        &in_triangle_open,
        &in_triangle_2,
        &in_triangle_2_open
    } ;

    for (int i = 0; i < 4; i++)
    {
        in_triangle_t fp = in_triangle_fns[i];

        assert( fp( pt(1,1),   pt(0,0), pt(0,3), pt(4,0) ));
        assert(!fp( pt(2,2),   pt(0,0), pt(0,3), pt(4,0) ));
        assert( fp( pt(1,2),   pt(0,0), pt(0,3), pt(4,0) ));
        assert(!fp( pt(0,6),   pt(0,0), pt(0,3), pt(4,0) ));
        assert(!fp( pt(6,0),   pt(0,0), pt(0,3), pt(4,0) ));
        
        // edge cases
        assert( fp( pt(2,0),   pt(0,0), pt(0,3), pt(4,0) ) == (i+1)%2 );
        assert( fp( pt(3,0),   pt(0,0), pt(0,3), pt(4,0) ) == (i+1)%2 );
        // corner cases
        assert( fp( pt(0,0),   pt(0,0), pt(0,3), pt(4,0) ) == (i+1)%2 );
        assert( fp( pt(0,3),   pt(0,0), pt(0,3), pt(4,0) ) == (i+1)%2 );
        assert( fp( pt(4,0),   pt(0,0), pt(0,3), pt(4,0) ) == (i+1)%2 );
    }
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
    typedef bool (*xptseg_t)(pt, pt, pt);
    xptseg_t xptseg_fns[] = 
    {
        &xPtSeg,
        &xPtSeg_open,
    } ;

    for (int i = 0; i < 2; i++)
    {
        xptseg_t fp = xptseg_fns[i];

        assert( fp( pt(3,3),  pt(2,2), pt(4,4) ));
        assert(!fp( pt(3,3),  pt(2,3), pt(4,4) ));
        assert( fp( pt(3,3),  pt(2,3), pt(4,3) ));
        assert( fp( pt(3,3),  pt(0,3), pt(9,3) ));
        assert(!fp( pt(3,4),  pt(3,3), pt(2,3) ));
        assert(!fp( pt(3,4),  pt(2,3), pt(3,3) ));
        assert(!fp( pt(3,3),  pt(2,2), pt(1,1) ));
        assert(!fp( pt(3,6),  pt(1,2), pt(2,4) ));
        // corner cases
        assert( fp( pt(3,3),  pt(3,3), pt(4,4) ) == (fp == &xPtSeg) );
        assert( fp( pt(3,3),  pt(3,3), pt(3,4) ) == (fp == &xPtSeg) );
        assert( fp( pt(3,3),  pt(3,3), pt(4,3) ) == (fp == &xPtSeg) );
        assert( fp( pt(3,3),  pt(4,4), pt(3,3) ) == (fp == &xPtSeg) );
        assert( fp( pt(3,3),  pt(3,3), pt(3,3) ) == (fp == &xPtSeg) );
        assert(!fp( pt(3,3),  pt(4,4), pt(4,4) ));
    }
}

void perpendicular_test()
{
    approx( perpendicular(pt( 1, 3)), pt(-3, 1) );
    approx( perpendicular(pt(-1, 3)), pt(-3,-1) );
    approx( perpendicular(pt( 0, 0)), pt( 0, 0) );
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
    perpendicular_test();
    return 0;
}


