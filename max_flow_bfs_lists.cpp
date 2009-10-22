/*
 * max_flow_bfs_lists.cpp
 *
 *  Created on: Nov 13, 2008
 *      Author: Chris
 */

/*
 * Runtime:	UVA820 0.020
 */

#include <map>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

typedef map<int, int> node;

const int N = 105;
int source, sink;
node graph[N];
int prev[N];

bool bfs() {
	fill(prev, prev + N, -1);
	queue<int> q;
	q.push(source);
	prev[source] = source;
	while (!q.empty()) {
		int c = q.front(); q.pop();
		if (c == sink) return true;
		for (node::iterator iter = graph[c].begin();
				iter != graph[c].end(); iter++) {
			int i = iter->first;
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
	int ret = 0;
	while (bfs()) ret += update();
	return ret ;
}


/*$*/
int main() {
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
/*$*/
