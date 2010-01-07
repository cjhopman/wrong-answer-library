#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class node
{
    public:
    node() : ix(-1), comp(-1), in_stack(0) {}
    vector<node *> edges;
    int ix;            // index in dfs; -1 represents undefined
    int lowlink;
    int in_stack;      // whether in dfs stack
    int comp;          // output: component to which this node belongs
};

vector<node *> G;        // input: directed graph as vector of nodes
int ix;                  // dfs visit index counter
int comp_ix;             // component counter
stack<node *> S;         // dfs stack

/*
 * Tarjan's algorithm for SCC
 * Graph is vector of nodes
 */
void tarjan_iter(node *v)
{
    v->ix = v->lowlink = ix++;
    S.push(v);
    v->in_stack = 1;

    for (int i = 0; i < v->edges.size(); i++)
    {
        node *z = v->edges[i];
        if (z->ix == -1)
        {
            tarjan_iter(z);
            v->lowlink = min(v->lowlink, z->lowlink);
        }
        else if (z->in_stack)
            v->lowlink = min(v->lowlink, z->ix);
    }

    if (v->lowlink == v->ix)
    {
        node *z;
        do
        {
            z = S.top(); S.pop();
            z->in_stack = 0;
            // z belongs to component comp_ix
        } while (z != v) ;

        comp_ix += 1;
    }
}

void tarjan(void)
{
    ix = 0;
    comp_ix = 0;
    S = stack<node *>();

    for (int i = 0; i < G.size(); i++)
        if (G[i]->ix == -1)
            tarjan_iter(G[i]);
}
