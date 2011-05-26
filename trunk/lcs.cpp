/* Longest common subsequence,
 * slow longest common substring
 * edit distance
 * Author: Zef RosnBrick
 */

#include <algorithm>

const int N = 100;
int s[N], t[N], slen, tlen, dp[N][N];

/*
 * Tested: UVA 10066
 */
void lcsequence()
{
	fill(dp[0], dp[N], 0);
	for (int i = 1; i <= slen; i++)
		for (int j = 1; j <= tlen; j++)
			dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), s[i - 1] == t[j - 1] ? 1 + dp[i - 1][j - 1] : 0);
}

void lcstring() {
	fill(dp[0], dp[N], 0);
	for (int i = 1; i <= slen; i++)
		for (int j = 1; j <= tlen; j++)
			dp[i][j] = s[i - 1] == t[j - 1] ? 1 + dp[i - 1][j - 1] : 0;
}

/*
 * Tested: UVA 164
 */
void edit_distance()
{
	for (int i = 0; i <= s.size(); i++)
		for (int j = 0; j <= t.size(); j++)
			if (i == 0 || j == 0)
				dp[i][j] = max(i, j);
			else if (s[i - 1] == t[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(min(dp[i - 1][j] + DEL, dp[i][j - 1] + INS), dp[i - 1][j - 1] + SUB);
}


/*$*/
#include <iostream>
#include <cstdio>

int main()
{
	int caseno = 0;

	while (++caseno)
	{
		if (!(cin >> slen >> tlen) || (slen == 0 && tlen == 0))
			break;

		for (int i  = 0; i < slen; i++)
			cin >> s[i];

		for (int i = 0; i < tlen; i++)
			cin >> t[i];

		lcsequence();

		printf("Twin Towers #%i\nNumber of Tiles : %i\n\n", caseno, dp[slen][tlen]);
	}

	return 0;
}
/*$*/
