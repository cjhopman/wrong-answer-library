/*
 * Floyd-Warshall All Pairs Shorest Paths
 *
 * Tested: UVA 821
 */

#include <algorithm>

#define INF 1000000000

using namespace std;

const int N = 100;
double dist[N][N];
int num_nodes;

void floyd_warshall()
{
	for (int k = 0; k < num_nodes; k++)
		for (int i = 0; i < num_nodes; i++)
			for (int j = 0; j < num_nodes; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

/*$*/
#include <iostream>
#include <cstdio>

int main()
{
	int caseno = 0, x, y, node_map[N];

	while (++caseno)
	{
		num_nodes = 0;

		fill(dist[0], dist[N], INF);
		for (int i = 0; i < N; i++)
			dist[i][i] = 0.0;

		fill(node_map, node_map + N, -1);
		while (cin >> x >> y && x != 0 && y != 0)
		{
			x--;
			y--;

			if (node_map[x] == -1)
				node_map[x] = num_nodes++;
			if (node_map[y] == -1)
				node_map[y] = num_nodes++;

			dist[node_map[x]][node_map[y]] = 1.0;
		}

		if (num_nodes == 0)
			break;

		floyd_warshall();

		double sum = 0.0;
		for (int i = 0; i < num_nodes; i++)
			for (int j = 0; j < num_nodes; j++)
				sum += dist[i][j];

		printf("Case %i: average length between pages = %.3f clicks\n", caseno, sum / (num_nodes * (num_nodes - 1)));
	}

	return 0;
}
/*$*/
