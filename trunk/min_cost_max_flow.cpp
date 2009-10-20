/*
 * TESTED ON ICPC Live 2691
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

const int N = 205;
int graph[N][N];
int cost[N][N];
int reduced_cost[N][N];
int potential[N];
int prev[N];

int source = N - 1, sink = N - 2;
const int INF = 10000000;

void reduce_cost() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (graph[i][j] >= 0)
				reduced_cost[i][j] += potential[i] - potential[j];
}

typedef pair<int, int> edge;
typedef pair<int, edge> q_pair;
#define to(x) ((x).second)
#define from(x) ((x).first)

int dijkstra() {
	reduce_cost();

	int best[N];
	fill(best, best + N, 2 * INF);
	fill(potential, potential + N, 2 * INF);
	fill(prev, prev + N, -1);
	priority_queue<q_pair, vector<q_pair>, greater<q_pair> > pq;

	pq.push(q_pair(0, edge(source, source)));

	while (!pq.empty()) {
		q_pair v = pq.top(); pq.pop();
		int c = v.first;
		int pv = from(v.second), curr = to(v.second);

		if (prev[curr] >= 0) continue;
		prev[curr] = pv;
		potential[curr] = c;

		if (c == sink) break;

		for (int next = 0; next < N; next++) {
			if (graph[curr][next] <= 0 || prev[next] >= 0) continue;
			if (best[next] < c + reduced_cost[curr][next]) continue;
			best[next] = c + reduced_cost[curr][next];
			pq.push(q_pair(best[next], edge(curr, next)));
		}
	}

	return potential[sink];
}

int update(int& v) {
	int ret = INF;
	for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
		ret = min(ret, graph[p][c]);
	for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
		v += cost[p][c] * ret, graph[p][c] -= ret, graph[c][p] += ret;
	return ret;
}


int min_cost_max_flow(int& c) {
	int flow = 0; c = 0;

	fill(potential, potential + N, INF);
	copy(cost[0], cost[N], reduced_cost[0]);
	potential[source] = 0;
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (graph[i][j] > 0)
					potential[j] = min(potential[j], potential[i] + cost[i][j]);

	while (dijkstra() < INF) flow += update(c);

	return flow;
}

int main() {
	int ncases;
	cin >> ncases;
	for (int caseno = 1; caseno <= ncases; caseno++) {
		if (caseno != 1) cout << endl;
		int num_buildings, num_shelters;

		vector<pair<int, int> > buildings, shelters;
		cin >> num_buildings >> num_shelters;
		fill(graph[0], graph[N], 0);
		fill(cost[0], cost[N], 0);

		for (int i = 0; i < num_buildings; i++) {
			int x, y, cap;
			cin >> x >> y >> cap;
			graph[source][i] = cap;
			buildings.push_back(pair<int, int>(x, y));
		}

		for (int i = 0; i < num_shelters; i++) {
			int x, y, cap;
			cin >> x >> y >> cap;
			graph[i + num_buildings][sink] = cap;
			shelters.push_back(pair<int, int>(x, y));
		}

		for (int i = 0; i < num_buildings; i++)
			for (int j = 0; j < num_shelters; j++) {
				cost[i][num_buildings + j] =
					1 + abs(buildings[i].first - shelters[j].first)
					+ abs(buildings[i].second - shelters[j].second);
				cost[num_buildings + j][i] = -cost[i][num_buildings + j];
				graph[i][num_buildings + j] = INF;
			}

		int c = 0, plan_cost = 0;
		min_cost_max_flow(c);

		for (int i = 0; i < num_buildings; i++)
			for (int j = 0; j < num_shelters; j++) {
				int p;
				cin >> p;
				plan_cost += p * cost[i][num_buildings + j];
			}

		if (c != plan_cost) {
			cout << "SUBOPTIMAL" << endl;
			for (int i = 0; i < num_buildings; i++) {
				for (int j = 0; j < num_shelters; j++) {
					cout << (j ? " " : "") << graph[num_buildings + j][i];
				}
				cout << endl;
			}
		} else cout << "OPTIMAL" << endl;
	}
	return 0;
}
