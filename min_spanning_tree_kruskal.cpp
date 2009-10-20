/*
 * min_spanning_tree_kruskal.cpp
 *
 * Tested.
 */


#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> edge;

const int N = 750;

int dist[N][N];
int rep[N];
int num_nodes;

int ds_find(int i) {
	return rep[i] == i ? i : rep[i] = ds_find(i);
}

void ds_union(int i, int j) {
	rep[ds_find(i)] = ds_find(j);
}

bool comp(const edge &a, const edge &b) {
	return dist[a.first][a.second] < dist[b.first][b.second];
}

void mst(vector<edge> &edges) {
	for (int i = 0; i < num_nodes; i++)
		for (int j = i + 1; j < num_nodes; j++)
			edges.push_back(edge(i, j));

	sort(edges.begin(), edges.end(), comp);

	int n = 0;
	for (int i = 0; i < edges.size(); i++)
		if (ds_find(edges[i].first) != ds_find(edges[i].second)) {
			ds_union(edges[i].first, edges[i].second);
			edges[n++] = edges[i];
		}

	edges.erase(pend, edges.end());
}
