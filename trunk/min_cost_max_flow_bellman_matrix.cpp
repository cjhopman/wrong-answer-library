/*
 * min_cost_max_flow_bellman.cpp
 *
 *  Created on: Nov 14, 2008
 *      Author: Chris
 */

/*
 * flow.cpp
 *
 *  Created on: Nov 14, 2008
 *      Author: Chris
 */


#include <map>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 205;
int source, sink, num_nodes;
int graph[N][N], cost[N][N];
bool visited[N];
int path[N];


bool bellman_ford(int& c) {
	int dist[N];
	fill(path, path + N, -1);
	fill(dist, dist + N, 100000000);
	dist[source] = 0;
	for (int t = 0; t < num_nodes; t++) {
		// technically algorithm iterates through edges here, but whatever
		for (int i = 0; i < num_nodes; i++) {
			for (int j = 0; j < num_nodes; j++) {
				if (graph[i][j] <= 0) continue;
				if (dist[j] > dist[i] + cost[i][j]) {
					dist[j] = dist[i] + cost[i][j];
					path[j] = i;
				}
			}
		}
	}
	c = dist[sink];
	return dist[sink] < 10000000;
}

int max_flow(long long& cost) {
	int flow = 0; cost = 0;
	int c = 0;
	while (bellman_ford(c)) {
		int prev = path[sink], curr = sink;
		prev = path[sink]; curr = sink;
		while (curr != source) {
			graph[curr][prev]++; graph[prev][curr]--;
			curr = prev; prev = path[prev];
		}
		flow++;
	}
	return flow;
}
