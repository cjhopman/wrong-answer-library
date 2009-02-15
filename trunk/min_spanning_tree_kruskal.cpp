/*
 * min_spanning_tree_kruskal.cpp
 *
 *  Created on: Nov 9, 2008
 *      Author: Chris
 */

/*
 * Tested.
 *
 */


#include <algorithm>
#include <vector>
#include <iostream>
#include <list>
#include <cmath>

using namespace std;

typedef pair<int,int> edge;

const int N = 750;

int dist[N][N];
int rep[N];
int num_nodes;

int ds_find(int i) {
	if (rep[i] == i) return i;
	return rep[i] = ds_find(rep[i]);
}

void ds_union(int i, int j) {
	rep[ds_find(i)] = ds_find(j);
}

bool comp(const edge &a, const edge &b) {
	return dist[a.first][a.second] < dist[b.first][b.second];
}

bool pred(const edge &a) {
	if (ds_find(a.first) == ds_find(a.second)) 
        return 1;
	ds_union(a.first, a.second); 
    return 0;
}

void mst(vector<edge> &edges) {
	for (int i = 0; i < num_nodes; i++)
		for (int j = i + 1; j < num_nodes; j++)
			edges.push_back(edge(i, j));

	sort(edges.begin(), edges.end(), comp);

	vector<edge>::iterator pend =
		remove_if(edges.begin(), edges.end(), pred);

	edges.erase(pend, edges.end());
}
