#include <vector>
#include <algorithm>

using namespace std;

class node
{
    public:
    node() : ix(-1), comp(-1), next(this) {}
    vector<node *> edges;
    int ix;            // index; -1 represents undefined
    int lowlink;
    node *next;        // elem below in stack (v->next == v denotes not in stack)
    int comp;          // component this node belongs to
};


vector<node *> G;        // input: directed graph
int ix = 0;              // dfs visit index counter
int comp_ix = 0;         // component counter
node *top;               // top of dfs visit stack
vector<node *> roots;    // output: root of each component

/*
 * Tarjan's algorithm for SCC
 * Graph is vector of nodes
 */
void tarjan_iter(node *v)
{
    v->ix = v->lowlink = ix++;
    v->next = top; top = v;           // push

    for (int i = 0; i < v->edges.size(); i++)
    {
        node *z = v->edges[i];
        if (z->ix == -1)
        {
            tarjan_iter(v);
            v->lowlink = min(v->lowlink, z->lowlink);
        }
        else if (z->next != z)                    // not in stack
            v->lowlink = min(v->lowlink, z->lowlink);
    }

    if (v->lowlink == v->ix)
    {
        do
        {
            top->comp = comp_ix;
            swap(top, top->next);                 // pop
        } while (top != v) ;
        roots.push_back(v);
        comp_ix += 1;
    }
}

void tarjan(void)
{
    for (int i = 0; i < G.size(); i++)
        if (G[i]->ix == -1)
            tarjan_iter(G[i]);
}

int main()
{
    return 0;
}
