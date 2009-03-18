// Fast Fourier Transform code
// Stuff to add:
//	Power of two Fourier transform
//

#include <iostream>
#include <utility>
#include <algorithm>
#include <complex>
#include <valarray>
#include <cmath>

using namespace std;

//Signal processing types
typedef long double			bigf;
typedef complex<bigf>		cbigf;
typedef valarray<cbigf>		distr;


//Uses the Cooley-Tukey algorithm to perform a Fourier transform of f.
// Note that size of f must be a power of two
//	Switching sign changes from fft to ifft
//NOT TESTED
distr fft(const distr& f, bigf sign = 1.)
{
	distr res(f.size());
	
	//Rearrange terms
	for(int t=0, p=0; p < f.size(); p++)
	{
		res[t] = f[p];
		int m = f.size();
		while(t & (m >>= 1))
			t &= ~m;
		t |= m;
	}
	
	//Execute fft
	for (int step = 1; step < f.size(); step <<= 1)
	{
		bigf delta = -sign * M_PI / bigf(step);
		cbigf m = exp(cbigf(0, delta)),
			  c = 1.;
		
		for(int g = 0; g < step; g++, c *= m)
		for(int p = g; p < f.size(); p += (step<<1))
		{
			int t = p + step;
			cbigf v = c * res[t];
			res[t] = res[p] - v;
			res[p] = res[p] + v;
		}
	}
	
	//Rescale
	if(sign < 0)
		res /= res.size();
	
	return res;
}

//Uses the FFT to quickly convolve a and b
distr conv(const distr a, const distr b)
{
	return fft( fft(a) * fft(b), -1.0 );
}


//Test code
int main(int argc, char** argv)
{
	distr A(1<<12), B(1<<12);
	
	for(int i=0; i<A.size(); i++)
	{
		A[i] = i;
		B[i] = 0.;
	}
	
	for(int i=0; i<4; i++)
	{
		B[i] = 1.;
	}
	
	cout << "A = " << endl;
	for(int i=0; i<A.size(); i++)
		cout << A[i] << endl;
	cout << endl;
	
	cout << "B = " << endl;
	for(int i=0; i<B.size(); i++)
		cout << B[i] << endl;
	cout << endl;
	
	distr C = conv(A, B);
	
	
	cout << "C = " << endl;
	for(int i=0; i<A.size(); i++)
		cout << C[i] << endl;
	cout << endl;
	
	return 0;
}
