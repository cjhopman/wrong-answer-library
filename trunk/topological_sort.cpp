/* Topological Sort
 * TESTED: UVA 10305 - Ordering Tasks
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class node
{
	public:
		node(int n): name(n), visited(false), in_cycle(false) {}
		int name;
		set<node *> in_edges, out_edges;
		bool visited, in_cycle;
};

vector<node *> nodes, L;

bool visit(node *n)
{
	if (!n->visited)
	{
		n->visited = n->in_cycle = true;
		for (set<node *>::iterator i = n->out_edges.begin(); i != n->out_edges.end(); i++)
			if (!visit(*i))
				return false;
		n->in_cycle = false;
		L.push_back(n);
	}
	return !n->in_cycle;
}


/*$*/
#include <map>
map<char, node *> nodemap;

int main()
{
	int caseno = 0, n, m, i, j;

	while (++caseno)
	{
		nodes.clear();
		L.clear();

		if (cin >> n >> m && n == 0 && m == 0)
			break;

		for (int t = 1; t <= n; t++)
			nodes.push_back(nodemap[t] = new node(t));

		for (int r = 0; r < m; r++)
		{
			cin >> i >> j;
			nodemap[i]->in_edges.insert(nodemap[j]);
			nodemap[j]->out_edges.insert(nodemap[i]);
		}

		for (vector<node *>::iterator it = nodes.begin(); it != nodes.end(); it++)
			if ((*it)->in_edges.size() == 0)
				if (!visit(*it))
					break;

		if (L.size() != nodes.size())
			cout << "Error" << endl;
		else
		{
			for (int t = 0; t < L.size(); t++)
			{
				if (t > 0)
					cout << " ";
				cout << L[t]->name;
			}
			cout << endl;
		}
	}

	return 0;
}
/*$*/
