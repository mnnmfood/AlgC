#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "stacks_queues/queue.h"

enum GColor
{
	white,
	gray,
	black
};

struct GNode
{
	int idx;
	int color;
	int p;
	int d;
	GNode(int i) : idx{ i }, color{ white }, 
		p{ -1 }, d{ std::numeric_limits<int>::max() } {}
	void update(int c) { color = c; }
};

struct GEdge
{
	GNode* u, * v;
	int w;
	GEdge(GNode* u_, GNode* v_, int weight) : u{ u_ }, v{ v_ }, w{ weight } {}
};

class UndiGraph
{
public:
	typedef GNode node;
	typedef GEdge edge;

	UndiGraph(int vn) : Vn{ vn } { 
		for (int i{ 0 }; i < vn; i++) {
			node_list.push_back(new node(i));
		}
		Adj.resize(Vn); 
	}
	UndiGraph(std::vector<std::vector<int>>& adj_m) { // from adj matrix
		if (check_square(adj_m)) build(adj_m);
		else if (check_triang(adj_m)) build_sparse(adj_m);
		else throw std::exception("Incorrect adjacency matrix\n");
	}
	void addEdge(int u, int v, int w=0) {
		assert((u < Vn) && "Index exceeded graph size\n");
		Adj[u].push_back(node_list[v]);
		edge_list.push_back(GEdge(node_list[u], node_list[v], w));
	}

	std::vector<GNode*> breadth_first(int si, int di) {
		Queue<node*> q(Vn);
		node* s = node_list[si];
		s->d = 0;
		s->color = gray;
		q.enqueue(s);
		while (!q.isEmpty()) {
			node* u = q.dequeue();
			for (int i{ 0 }; i < Adj[u->idx].size(); i++) {
				node* v = Adj[u->idx][i];
				if (v->color == white) {
					v->d = u->d + 1;
					v->color = gray;
					v->p = u->idx;
					q.enqueue(v);
				}
			}
			u->color = black;
		}
		node* d = node_list[di];
		std::vector<GNode*> res;
		while (d->p != -1) {
			res.push_back(d);
			d = node_list[d->p];
		}
		res.push_back(d);
		return res;
	}

	friend std::vector<GEdge> Kruskal(UndiGraph);
protected:
	int En; // num edges
	int Vn; // num vertices
	std::vector<std::vector<GNode*>> Adj; // adjacency list
	std::vector<node*> node_list;
	std::vector<edge> edge_list;

	void build(std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			for (int k{ 0 }; k < (n_rows-i); k++) {
				node* u = node_list[k];
				if (m[i][k] != 0) Adj[i].push_back(u);
			}
		}
	}
	void build_sparse(std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			for (int k{ 0 }; k < i; k++) {
				node* u = node_list[k];
				if (m[i][k] != 0) Adj[i].push_back(u);
			}
		}
	}

	int check_square(std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			std::vector<int> row = m[0];
			if (row.size() != n_rows) return 0;
		}
		return 1;
	}
	int check_triang (std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			std::vector<int> row = m[0];
			if (row.size() != (n_rows-i)) return 0;
		}
		return 1;
	}
};

#endif