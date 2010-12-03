#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class cell
{
	public:
		cell(int i) : ix(i) {}

		int ix;

		int out_edges;
		vector<cell *> in_edges;

		bool visited;
		bool in_cycle;
};

vector<cell *> S;
vector<cell *> L;
bool cyclic;

void visit(cell *n)
{
	if (n->in_cycle)
		cyclic = true;

	if (!n->visited)
	{
		n->visited = true;
		n->in_cycle = true;
		for (int i = 0; i < n->in_edges.size(); i++)
			visit(n->in_edges[i]);
		L.push_back(n);
		n->in_cycle = false;
	}
}

bool topological_sort()
{
	for (int i = 0; i < S.size(); i++)
		if (S[i]->out_edges == 0)
			visit(S[i]);

	for (int i = 0; i < S.size(); i++)
		if (!S[i]->visited)
			cyclic = true;

	return !cyclic;
}

void add_dependency(cell *indep, cell *dep)
{
	dep->in_edges.push_back(indep);
	indep->out_edges++;
}

int main()
{
	int caseno = 0, n, m, a, b;
	while (++caseno)
	{
		cin >> n >> m;

		if (n == 0 && m == 0)
			return 0;

		S.clear();
		L.clear();

		for (int i = 1; i <= n; i++)
			S.push_back(new cell(i));

		for (int i = 0; i < m; i++)
		{
			cin >> a >> b;
			add_dependency(S[a - 1], S[b - 1]);
		}

		topological_sort();

		for (int i = 0; i < L.size(); i++)
			cout << (i > 0 ? " " : "") << L[i]->ix;
		cout << endl;
	}
}
