#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <queue>

using namespace std;

const int N = 205;
int graph[N][N];
int cost[N][N];
int reduced_cost[N][N];
int potential[N];
bool visited[N];
int path[N];

int source = N - 1, sink = N - 2;
const int INF = 10000000;
void reduce_cost() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (graph[i][j] >= 0)
				reduced_cost[i][j] += potential[i] - potential[j];
}

int djikstra() {
	reduce_cost();
	typedef pair<int, int> edge;
	typedef pair<int, edge> q_pair;
	
	fill(potential, potential + N, 2 * INF);
	fill(visited, visited + N, 0);
	priority_queue<q_pair, vector<q_pair>, greater<q_pair> > pq;
	pq.push(q_pair(0, edge(-1, source)));
	
	while (!pq.empty()) {
		q_pair v = pq.top(); pq.pop();
		int c = v.first;
		int prev = v.second.first, curr = v.second.second;
		
		if (visited[curr]) continue;
		visited[curr] = true;
		path[curr] = prev;
		potential[curr] = c;
		
		for (int next = 0; next < N; next++) {
			if (graph[curr][next] <= 0 || visited[next]) continue;
			pq.push(q_pair(c + reduced_cost[curr][next], edge(curr, next)));
		}
	}
	
	return potential[sink];
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
		
	while (djikstra() < INF) {
		int cap = 10000000;
		int len = 0;
		
		for (int curr = sink, prev = path[curr]; curr != source; curr = prev, prev = path[curr]) {
			cap = min(cap, graph[prev][curr]);
		}

		for (int curr = sink, prev = path[curr]; curr != source; curr = prev, prev = path[curr]) {
			graph[curr][prev] += cap;
			graph[prev][curr] -= cap;
			len += cost[prev][curr];
		}
		
		flow += cap;
		c += cap * len;
	}
		
	
	return flow;
}

int main() {
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
		graph[i][num_buildings + j] = 1000000;
	}
	
	int c = 0, plan_cost = 0;
	min_cost_max_flow(c);
	
	for (int i = 0; i < num_buildings; i++)
	for (int j = 0; j < num_shelters; j++) {
		int p;
		cin >> p;
		plan_cost += p * cost[i][num_buildings + j];
	}
	
	for (int i = 0; i < num_buildings; i++) {
	for (int j = 0; j < num_shelters; j++) {
		cout << graph[num_buildings + j][i] << " ";
	}
	cout << endl;
	}
	
	cout << c << " " << plan_cost << endl;
	
	return 0;
}
