//Bit twiddling hacks go here
// Stuff to add:
//	Combination generation



#include <iostream>

using namespace std;

typedef unsigned long long big;


big next_combo(big x)
{
    big b = x & (-x);
    big t = x + b;
    return t | (((x^t) >> 2) / b);
}

void generate_combos(big n, big k)
{
    for(big x=(1<<(k))-1; x<(((big)1)<<n); x = next_combo(x))
    {
    
        //Do stuff with combination x
        for(big i=0; i<n; i++)
            cout << ((x & ((big)1<<i)) != 0 ? '1' : '0');
        cout << endl;
        
    }
}

int main(int argc, char ** argv)
{
    generate_combos(50, 3);
    
    return 0;
}


