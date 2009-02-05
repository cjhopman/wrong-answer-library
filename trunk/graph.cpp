/*
 * graph.cpp
 *
 *  Created on: Nov 6, 2008
 *      Author: Chris
 */

#include <vector>
#include <map>
#include <queue>
#include <algorithm>


using namespace std;

namespace graph {

	template <typename node_type, typename cost_type = int>
	struct list_graph {
		vector<node_type> nodes;
		vector<map<int, cost_type> > edges;
		bool edge(int i, int j) { return edges[i].contains(j); }
		map<int, cost_type>& operator[](int i) { return edges[i]; }
		node_type& operator()(int i) { return nodes[i]; }
		void add_edge(int i, int j, cost_type cost = cost_type(1)) { edges[i][j] = cost; }
		void add_node(node_type& n) { nodes.push_back(n); }
		int size() { return nodes.size(); }
	};

	template <typename node_type, typename cost_type = int>
	struct matrix_graph {
		vector<node_type> nodes;
		vector<vector<cost_type> > edges;
		int cap;

		void expand(int n) {
			cap = n;
			nodes.reserve(n);
			edges.resize(n);
			for_each(edges.begin(), edges.end(), bind2nd(mem_fun(&vector<cost_type>::resize), n));
		}

		bool edge(int i, int j) { return edges[i][j]; }
		vector<cost_type>& operator[](int i) { return edges[i]; }
		node_type& operator()(int i) { return nodes[i]; }
		void add_edge(int i, int j, cost_type cost = cost_type(1)) { edges[i][j] = cost; }
		void add_node(node_type& N) { nodes.push_back(N); }
		int size() { return nodes.size(); }
	};

	template <typename graph_type>
	bool dfs(graph_type& graph, int start, int end, vector<int>& path = vector<int>(),
			vector<char>& visited = vector<char>()) {
		if (visited.empty()) visited.resize(graph.size());
		if (visited[start]) return false;
		visited[start] = 1;

		path.push_back(start);
		if (start == end) return true;
		for (int i = 0; i < graph[start].size(); i++) {
			if (!graph.edge(start, i)) continue;
			if (dfs(graph, graph[start][i], end, path, visited)) return true;
		}
		path.pop_back();
		return false;
	}

	template <typename graph_type>
	bool bfs(graph_type& graph, int start, int end, vector<int>& path = vector<int>()) {
		vector<char> visited(graph.size());

		vector<int> prev(graph.size());
		queue<int> q;
		q.push(start);
		while (!q.empty()) {
			int n = q.front();
			if (n == end) break;
			q.pop();

			for (int i = 0; i < graph[n].size(); i++) {
				if (!graph.edge(n, i)) continue;
				if (visited[i]) continue;
				visited[i] = 1;
				q.push(i);
				prev[i] = n;
			}
		}

		if (q.empty()) return false;
		for (int n = end; n != start; n = prev[n]) path.push_back(n);
		path.push_back(start);
		reverse(path.begin(), path.end());
		return true;
	}

	template <typename T, typename cost_type>
	bool operator<(const pair<T, cost_type>& a,
			const pair<T, cost_type>& b)
	{ return a.second < b.second; }

	template <typename graph_type>
	bool djikstra(graph_type& graph, int start, vector<typename graph_type::cost_type>& costs,
			bool find_paths = false, vector<vector<int> >& paths = vector<vector<int> >()) {

		typedef typename graph_type::cost_type cost_type;
		typedef pair<int, int> edge;
		typedef pair<edge, cost_type> q_pair;

		vector<int> prev(graph.size());
		vector<bool> visited(graph.size());

		priority_queue<q_pair>  pq;
		pq.push(q_pair(edge(start, -1), cost_type(0)));
		while (!pq.empty()) {
			q_pair p = pq.front();
			int n = p.first.first;
			pq.pop();

			if (visited[n]) continue;
			visited[n] = true;

			prev[n] = p.first.second;

			for (int i = 0; i < graph[n].size(); i++) {
				if (!graph.edge(n, i)) continue;
				pq.push(q_pair(edge(i, n), p.second + graph[i][n]));
			}
		}

		if (!find_paths) return;
		paths.resize(graph.size());
		for_each(paths.begin(), paths.end(), bind2nd(mem_fun(&vector<int>::resize), graph.size()));

		for (int i = 0; i < paths.size(); i++) {
			paths[i].push_back(i);
			for (int n = prev[i]; n != -1; n = prev[n]) paths[i].push_back(n);
			reverse(paths[i].begin(), paths[i].end());
		}
	}
}
