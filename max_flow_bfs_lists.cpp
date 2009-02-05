/*
 * max_flow_bfs_lists.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: Chris
 */

/*
 * Runtime:	UVA820 0.990
 *
 *
 */

#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

typedef map<int, int> node;

const int N = 105;
int source, sink;
node graph[N];
bool visited[N];
int path[N];

bool bfs(int from = source, int to = sink) {
	fill(visited, visited + N, false);
	queue<int> q;
	q.push(source);
	while (!q.empty()) {
		int n = q.front(); q.pop();
		if (n == sink) return true;
		for (node::iterator iter = graph[n].begin(); iter != graph[n].end(); iter++) {
			if (visited[iter->first] || iter->second <= 0) continue;
			path[iter->first] = n;
			q.push(iter->first);
			visited[iter->first] = true;
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

int flow_bfs_lists_main() {
	int network_id = 1;
	while (true) {
		int num_nodes, num_edges;
		scanf("%d", &num_nodes);
		if (!num_nodes) break;

		for_each(graph, graph + N, mem_fun_ref(&node::clear));
		scanf("%d %d %d", &source, &sink, &num_edges);

		for (int i = 0; i < num_edges; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			graph[a][b] = graph[b][a] += c;
		}

		printf("Network %d\nThe bandwidth is %d.\n\n", network_id++, max_flow());
	}
}
