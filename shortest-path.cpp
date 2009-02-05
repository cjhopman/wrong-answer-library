/*
 * shortest-path.cpp
 *
 *  Created on: Nov 14, 2008
 *      Author: Chris
 */


#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <sstream>
#include <string>

/*
 * Tested: UVA10801
 */

using namespace std;

typedef map<int, int> node;

const int N = 1005;
int source, sink;
node graph[N];
int path[N];
bool visited[N];

typedef pair<int, int> edge;
typedef pair<int, edge> q_pair; // <cost, <to, from> > --- default < compares cost first

bool bfs(int& c) {
	fill(visited, visited + N, false);
	priority_queue<q_pair, vector<q_pair>, greater<q_pair> > q;
	q.push(q_pair(0, edge(source, -1)));
	while (!q.empty()) {
		q_pair qp = q.top(); q.pop();
		int n = qp.second.first;
		path[n] = qp.second.second;
		visited[n] = true;
		if (n == sink) { c += qp.first; return true; }
		for (node::iterator iter = graph[n].begin(); iter != graph[n].end(); iter++) {
			if (visited[iter->first]) continue;
			q.push(q_pair(qp.first + graph[n][iter->first], edge(iter->first, n)));
		}
	}
	return false;
}
bool dfs(int &c)
{
	void *n = malloc(sizeof(int));
	memset(n, 0, sizeof(int));
	return 0;

}
