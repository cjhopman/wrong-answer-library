#include "../geom_poly.cpp"

#include <iostream>
#include <cassert>
#include <cmath>

#include <vector>

vector<polygon> test_pp;

void initialize_test_polygons()
{
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0) break;
        polygon V;
        for (int i = 0; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            V.push_back(pt(x,y));
        }
        test_pp.push_back(V);
    }
}

void area_polygon_test()
{

}

int main (int argc, char **argv)
{
    initialize_test_polygons();
    area_polygon_test();
    return 0;
}


