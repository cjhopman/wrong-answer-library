/* simplified BigInt implementation
 * usage: good enough for almost any counting problem
 */

#include <valarray>
#include <iostream>
using namespace std;

const int N = 26;

struct big {
	valarray<unsigned long long> vals;
	big() : vals(N) { }
	big(unsigned long long a) : vals(N) { vals[0] = a; carry(); }
	big& operator+=(const big& o) {
		vals += o.vals;
		return carry();
	}
	big& carry() {
		for (int i = 1; i < N; i++)
			vals[i] += vals[i - 1] / 100000000, vals[i - 1] %= 100000000;
		return *this;
	}
};

bool operator<(const big& a, const big& b) {
	for (int i = N - 1; i >= 0; i--)
		if (a.vals[i] != b.vals[i]) return a.vals[i] < b.vals[i];
	return 0;
}
bool operator>(const big& a, const big& b) {
	return b < a;
}

ostream& operator<<(ostream& o, const big& a) {
	int s = N - 1;
	while (s != 0 && !a.vals[s]) s--;
	for (int t = s; t >= 0; t--) {
		if (t != s) {
			int K = 10000000;
			while (K > a.vals[t]) { o << 0; K /= 10; }
		}
		o << a.vals[t];
	}
	return o;
}



/*$*/
int main() {
	big p(1), c(1), t, top;
	top.vals[6] = 1;
	cout << top;
	for (int i = 0; i < 1000; i++) {
		cout << c << endl;
		if (c > top) break;
		t = c;
		c += p;
		p = t;
	}
	return 0;
}
/*$*/
