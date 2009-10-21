/* Longest increasing subsequence
 * NOT TESTED
 */

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
	fill(m, m + N, len);
	m[0] = 0;
	prev[0] = -1;
	for (int i = 1; i < len; i++) {
		int p = lower_bound(m, m + ret, i, comp);
		prev[i] = m[j];
		if (seq[i] < seq[m[j + 1]]) m[j + 1] = i;
		ret = max(ret, j + 1);
	}
	return ret;
}

