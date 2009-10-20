/* generate combinations
 * usage: generates combinations and permutations lexicographically
 * generates over range [0, n-1]
 *
 * generates kth lexicographic permutation (perm(n, n)).
 */

#include <iostream>

using namespace std;

void generate_combos(int n, int k) {
	int com[100];
	for (int i = 0; i < k; i++) com[i] = i;
	while (com[k - 1] < n) {

		for (int i = 0; i < k; i++)
			cout << (i ? ", " : "") << com[i];
		cout << endl;

		int t = k - 1;
		while (t != 0 && com[t] == n - k + t) t--;
		com[t]++;
		for (int i = t + 1; i < k; i++) com[i] = com[i - 1] + 1;
	}
}

void generate_permutations(int n, int k) {
	int perm[100];
	for (int i = 0; i < n; i++) perm[i] = i;
	int j = k;
	while (true) {

		for (int i = 0; i < k; i++)
			cout << (i ? ", " : "") << perm[i];
		cout << endl;

		if (j < n) {
			swap(perm[k - 1], perm[j++]);
		} else {
			int t = k - 2;
			while (t >= 0 && perm[t] > perm[t + 1]) t--;
			if (t < 0) break;
			rotate(perm + t + 1, perm + k, perm + n);
			swap(perm[t], *lower_bound(perm + t + 1, perm + n, perm[t]));
			j = k;
		}
	}
}

void kth_permutation(int n, int k) {
	int perm[100];
	for (int i = 0; i < n; i++) perm[i] = i;
	long long fact = 1;
	for (int i = 2; i < n; i++) fact *= i;
	for (int i = 0; i < n - 1; i++) {
		int t = (k / fact) % (n - i);
		rotate(perm + i, perm + i + t, perm + i + t + 1);
		fact /= n - i - 1;
	}

	for (int i = 0; i < n; i++)
		cout << perm[i] << " ";
	cout << endl;
}


int main(int argc, char ** argv)
{
	//generate_permutations(50, 3);
	//generate_combos(50, 3);
	for (int i = 0; i < 6; i++)
		kth_permutation(3, i);
    return 0;
}


