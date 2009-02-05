/*
 * max_flow_bfs_matrix.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: Chris
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
int num_nodes;

bool bfs(int from = source, int to = sink) {
	fill(visited, visited + N, false);
	queue<int> q;
	q.push(from);
	while (!q.empty()) {
		int n = q.front(); q.pop();
		if (n == to) return true;
		for (int i = 0; i < N; i++) {
			if (visited[i] || graph[n][i] <= 0) continue;
			path[i] = n;
			q.push(i);
			visited[i] = true;
		}
	}
	return false;
}

int max_flow() {
	int flow = 0;
	while (bfs()) {
		flow++;
		int prev = path[sink], curr = sink;
		while (curr != source) {
			graph[curr][prev]++; graph[prev][curr]--;
			curr = prev; prev = path[prev];
		}
	}
	return flow;
}

int flow_bfs_matrix_main() {
	int network_id = 1;
	while (true) {
		int num_edges;
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
