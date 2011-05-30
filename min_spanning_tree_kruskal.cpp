/*
 * min_spanning_tree_kruskal.cpp
 *
 * Tested: UVA 10147
 */


#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> edge;

const int N = 750;

double dist[N][N];
int rep[N];
int num_nodes;

int ds_find(int i) {
	return rep[i] == i ? i : rep[i] = ds_find(rep[i]);
}

void ds_union(int i, int j) {
	rep[ds_find(i)] = ds_find(j);
}

bool comp(const edge &a, const edge &b) {
	return dist[a.first][a.second] < dist[b.first][b.second];
}

#include <iostream>

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

	edges.erase(edges.begin() + n, edges.end());
}

/*$*/
#include <complex>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>

typedef complex<double> pt;

int main()
{
	int ncases, m, a, b;
	double x, y;
	pt towns[N];
	vector<edge> edges;
	map<edge, bool> existing;

	cin >> ncases;
	for (int caseno = 1; caseno <= ncases; caseno++)
	{
		if (caseno > 1)
			cout << endl;

		cin >> num_nodes;
		for (int i = 0; i < num_nodes; i++)
		{
			cin >> x >> y;
			rep[i] = i;
			towns[i] = pt(x, y);
			for (int j = 0; j < i; j++)
				dist[i][j] = dist[j][i] = abs(towns[i] - towns[j]);
		}

		edges.clear();
		existing.clear();

		cin >> m;
		for (int i = 0; i < m; i++)
		{
			cin >> a >> b;
			existing[edge(a - 1, b - 1)] = true;
			ds_union(a - 1, b - 1);
		}

		mst(edges);

		bool all = true;
		for (int i = 0; i < edges.size(); i++)
			if (existing.count(edges[i]) == 0 && (all = false) == false)
				cout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;

		if (all)
			cout << "No new highways need" << endl;
	}

	return 0;
}
/*$*/
