/*
 * max_flow_dfs_matrix.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: Chris
 */

/*
 * Runtime:	UVA820 1.270
 *
 *
 */

#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 105;
int source, sink;
int graph[N][N];
bool visited[N];
int path[N];

bool dfs(int n = source, int to = sink) {
	if (visited[n]) return false;
	if (n == to) return true;
	visited[n] = true;
	for (int i = 0; i < N; i++) {
		if (visited[i] || graph[n][i] <= 0) continue;
		path[n] = i;
		if (dfs(i, to)) return true;
	}
	return false;
}

int max_flow() {
	fill(visited, visited + N, false);
	int flow = 0;
	while (dfs()) {
		fill(visited, visited + N, false);
		flow++;
		int curr = source, next = path[source];
		while (curr != sink) {
			graph[curr][next]--; graph[next][curr]++;
			curr = next; next = path[next];
		}
	}
	return flow;
}

int flow_dfs_matrix_main() {
	int network_id = 1;
	while (true) {
		int num_nodes, num_edges;
		scanf("%d", &num_nodes);
		if (!num_nodes) break;

		fill(graph[0], graph[0] + N * N, 0);

		scanf("%d %d %d", &source, &sink, &num_edges);

		for (int i = 0; i < num_edges; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			graph[a][b] = graph[b][a] += c;
		}

		printf("Network %d\nThe bandwidth is %d.\n\n", network_id++, max_flow());
	}
}
