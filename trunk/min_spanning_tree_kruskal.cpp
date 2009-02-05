/*
 * min_spanning_tree_kruskal.cpp
 *
 *  Created on: Nov 9, 2008
 *      Author: Chris
 */


#include <algorithm>
#include <vector>
#include <iostream>
#include <list>
#include <cmath>

using namespace std;

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

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
	return dist[a.first][a.second] < dist[b.first][b.second];
}

bool pred(const pair<int, int>& a) {
	if (ds_find(a.first) == ds_find(a.second)) return true;
	ds_union(a.first, a.second); return false;
}

void mst(vector<pair<int, int> >& edges) {
	for (int i = 0; i < num_nodes; i++)
		for (int j = i + 1; j < num_nodes; j++)
			edges.push_back(pair<int, int>(i, j));

	sort(edges.begin(), edges.end(), comp);

	vector<pair<int, int> >::iterator pend =
		remove_if(edges.begin(), edges.end(), pred);

	edges.erase(pend, edges.end());
}
