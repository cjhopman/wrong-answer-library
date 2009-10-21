/* Longest common subsequence, slow longest common substring
 * edit distance
 * NOT TESTED
 */

#include <string>

const int N = 100;
string s, t;
int dp[N][N];

void lcsequence() {
	fill(dp[0], dp[N], 0);
	for (int i = 1; i <= s.size(); i++)
		for (int j = 1; j <= t.size(); j++)
			dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), s[i - 1] == t[j - 1] ? 1 + dp[i - 1][j - 1] : 0);
}

void lcstring() {
	fill(dp[0], dp[N], 0);
	for (int i = 1; i <= s.size(); i++)
		for (int j = 1; j <= t.size(); j++)
			dp[i][j] = s[i - 1] == t[j - 1] ? 1 + dp[i - 1][j - 1] : 0;
}

void edit_dist() {
	for (int i = 0; i < N; i++)
		dp[i][0] = dp[0][i] = i;
	for (int i = 1; i <= s.size(); i++)
		for (int j = 1; j <= t.size(); j++)
			dp[i][j] = s[i - 1] == t[j - 1] ? dp[i - 1][j - 1]
				: 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
}

