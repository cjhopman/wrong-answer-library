/*
 * shortest-path.cpp
 *
 * Tested: UVA10801
 */


#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int N = 101;
int source, sink;
int graph[N][N];
int prev[N];

typedef pair<int, int> pii;

bool dijkstra(int& cost) {
	int dist[N];
	fill(dist, dist + N, 1000000000);
	fill(prev, prev + N, -1);

	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push(pii(0, source));
	dist[source] = 0;
	prev[source] = source;

	while (!pq.empty()) {
		pii curr = pq.top(); pq.pop();
		int c = curr.second;

		if (dist[c] < curr.first) continue;
		if (c == sink) { cost += curr.first; return true; }

		for (int n = 0; n < N; n++) {
			if (dist[n] <= curr.first + graph[c][n]) continue;
			dist[n] = curr.first + graph[c][n];
			prev[n] = c;
			pq.push(pii(dist[n], n));
		}
	}
	return false;
}
/*$*/
int main() {
	int n;
	while (cin >> n >> sink) {
		int sp[N];
		for (int i = 0; i < n; i++)
			cin >> sp[i];
		string line;
		getline(cin, line);
		fill(graph[0], graph[N], 1000000000);
		for (int e = 0; e < n; e++) {
			getline(cin, line);
			stringstream in(line);
			int stops[N];
			int ns = 0;
			while (in >> stops[ns]) { ns++; }
			for (int i = 0; i < ns; i++) {
				for (int j = 0; j < i; j++) {
					int s = stops[i], t = stops[j];
					graph[s][t] = graph[t][s] = min(graph[s][t] == 0 ?
							1000000000 : graph[s][t], abs(s - t) * sp[e] + 60);
				}
			}
		}

		int c = 0;
		source = 0;
		if (!sink) cout << 0 << endl;
		else if (dijkstra(c)) cout << c - 60 << endl;
		else cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
/*$*/

