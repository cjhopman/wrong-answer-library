/* Longest increasing subsequence
 * TESTED: UVA 481
 */
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000000;
int seq[N];
int m[N];
int prev[N];
int len;

bool comp(int a, int b) {
	return seq[a] < seq[b];
}


int lis() {
	int ret = 1;
	seq[len] = 1000000000;
	fill(m, m + len, len);
	m[0] = 0;
	prev[0] = -1;
	for (int i = 1; i < len; i++) {
		// upper_bound for non-decreasing
		int p = lower_bound(m, m + ret, i, comp) - m - 1;
		prev[i] = m[p];
		if (seq[i] < seq[m[p + 1]]) m[p + 1] = i;
		ret = max(ret, p + 2);
	}
	return ret;
}



/*$*/
void print(int i) {
	if (i < 0) return;
	print(prev[i]);
	cout << seq[i] << endl;
}

int main() {
	for (len = 0; cin >> seq[len];) { len++; }
	cout << (len = lis()) << endl;
	cout << "-" << endl;
	print(m[len - 1]);
	return 0;
}
/*$*/

