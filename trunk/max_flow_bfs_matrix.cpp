/*
 * max_flow_bfs_matrix.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: Chris
 */

/*$
 * Runtime:	UVA820 0.024
 $*/

#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 105;
int source, sink;
int graph[N][N];
int prev[N];
int num_nodes;

bool bfs() {
	fill(prev, prev + N, -1);
	queue<int> q;
	q.push(source);
	prev[source] = source;
	while (!q.empty()) {
		int c = q.front();
		q.pop();
		if (c == sink) return true;
		for (int i = 0; i < N; i++) {
			if (prev[i] >= 0 || graph[c][i] <= 0) continue;
			prev[i] = c;
			q.push(i);
		}
	}
	return false;
}

int update() {
	int ret = 1000000000;
	for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
		ret = min(ret, graph[p][c]);
	for (int c = sink, p = prev[c]; c != source; c = p, p = prev[c])
		graph[p][c] -= ret, graph[c][p] += ret;
	return ret;
}

int max_flow() {
	int flow = 0;
	while (bfs()) {
		flow += update();
	}
	return flow;
}

/*$*/
int main() {
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
/*$*/
