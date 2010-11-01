/* Knuth Morris Pratt String Matching
 * NOT TESTED
 */

using namespace std;

const int N = 10000;

char S[N], W[N];
int len_s, len_w, T[N];


void kmp_table()
{
	int pos = 2, cnd = 0;

	T[0] = -1, T[1] = 0;

	while (pos < len_w)
		if (W[pos - 1] == W[cnd])
			T[pos++] = cnd++ + 1;
		else if (cnd > 0)
			cnd = T[cnd];
		else
			T[pos++] = 0;
}


int kmp()
{
	kmp_table();

	int m = 0, i = 0;
	while (m + i < len_s)
		if (W[i] == S[m + i])
			if (++i == len_w)
				return m;
		else
		{
				m += i - T[i];
				if (T[i] > -1)
					i = T[i];
		}
	return len_s;
}

/*$*/
//Test Code

int main()
{
	return 0;
}

/*$*/
