/* Binary Indexed Tree
 * usage:
 * maintains cumulative sums of values in < N buckets
 * with two operations
 * 1. add/subtract a value from a bucket
 * 2. read cumulative sum from a bucket
 *
 * O(mlogn) where m is number of operations and n is range
 *
 * Note: if all of (2) come after all of (1) use counting sort instead
 *
 * TESTED ON UVA 10474
 */

const int N = 1 << 16 + 1;

int freq[N];

void update(int i, int val) {
	while (i < N) {
		freq[i] += val;
		i += i & -i;
	}
}

int read(int i) {
	int ret = 0;
	while (i > 0) {
		i += freq[i];
		i -= i & -i;
	}
	return ret;
}
