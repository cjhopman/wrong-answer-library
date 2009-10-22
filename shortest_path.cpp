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

typedef pair<int, int> edge;
// <cost, <from, to> > --- default < compares cost first
typedef pair<int, edge> q_pair;

bool dijkstra(int& cost) {
	int best[N];

	fill(prev, prev + N, -1);
	fill(best, best + N, 1000000000);

	priority_queue<q_pair, vector<q_pair>, greater<q_pair> > pq;
	pq.push(q_pair(0, edge(source, source)));
	best[0] = 0;

	while (!pq.empty()) {
		q_pair curr = pq.top(); pq.pop();
		int c = curr.second.second;

		if (best[c] <= curr.first) continue;
		prev[c] = curr.second.first;
		if (c == sink) { cost += curr.first; return true; }

		for (int n = 0; n < N; n++) {
			if (graph[c][n] > 100000000) continue;
			if (best[n] <= curr.first + graph[c][n]) continue;
			best[n] = curr.first + graph[c][n];
			pq.push(q_pair(best[n], edge(c, n)));
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

