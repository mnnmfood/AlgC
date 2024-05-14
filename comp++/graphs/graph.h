#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "stacks_queues/queue.h"
#include "sets/DisjForest.h"
#include "trees/fibonacci_heap.h"
#include "graphs/matrices.h"

inline const int MAX_INT = std::numeric_limits<int>::max();

enum GColor
{
	white,
	gray,
	black
};

struct GNode: public DisjNode<int>, public FBNode<int>
{
	int idx, color, pi, d;
	GNode(int i) : idx{ i }, color{ white }, 
		pi{ -1 }, d{ std::numeric_limits<int>::max() } {}
	void update(int c) { color = c; }
};

struct GEdge
{
	GNode* u, * v;
	int w;
	int c, flow; // capacity and flow -used for maximum flow algorithms
	GEdge(GNode* u_, GNode* v_, int weight) : u{ u_ }, v{ v_ }, w{ weight }, 
		c{ -1 }, flow{ -1 } {}
	GEdge(GNode* u_, GNode* v_, int weight, int _c, int _f) : u{ u_ }, v{ v_ }, 
		w{ weight }, c{ _c }, flow{ _f }{}
};

class Graph
{
public:
	typedef GNode node;
	typedef GEdge edge;

	Graph(int vn) : Vn{ vn }, W{ vn } {
		for (int i{ 0 }; i < vn; i++) {
			node_list.push_back(new node(i));
		}
		Adj.resize(Vn); 
		initializeW(Vn);
	}

	Graph(std::vector<std::vector<int>>& adj_m) 
		:Vn{ static_cast<int>(adj_m.size()) }, W(adj_m.size())
	{ // from adj matrix
		initializeW(Vn);
		if (check_square(adj_m)) build(adj_m);
		else if (check_triang(adj_m)) build_sparse(adj_m);
		else throw std::exception("Incorrect adjacency matrix\n");
	}
	void addEdgeUndir(int u, int v, int w=0, int c=0, int f=0) {
		assert((u < Vn) && "Index exceeded graph size\n");
		GEdge edge(node_list[u], node_list[v], w, c, f);
		GEdge edge2(node_list[v], node_list[u], w, c, f);
		Adj[u].push_back(edge);
		Adj[v].push_back(edge2);
		edge_list.push_back(edge);
		edge_list.push_back(edge2);
		W(u, v) = W(v, u) = w;
	}

	void addEdgeDir(int u, int v, int w=0, int c=0, int f=0) {
		assert((u < Vn) && "Index exceeded graph size\n");
		GEdge edge(node_list[u], node_list[v], w, c, f);
		Adj[u].push_back(edge);
		edge_list.push_back(edge);
		W(u, v) = w;
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
				node* v = Adj[u->idx][i].v;
				if (v->color == white) {
					v->d = u->d + 1;
					v->color = gray;
					v->pi = u->idx;
					q.enqueue(v);
				}
			}
			u->color = black;
		}
		node* d = node_list[di];
		std::vector<GNode*> res;
		while (d->pi != -1) {
			res.push_back(d);
			d = node_list[d->pi];
		}
		res.push_back(d);
		return res;
	}
	
	int isEdge(int u, int v) {
		return static_cast<int>(W(u, v) < MAX_INT);
	}

	void reset() {
		edge_list.resize(0);
		En = 0;
		W.setConstant(0);
	}

	friend std::vector<GEdge> Kruskal(Graph&);
	friend std::vector<GEdge> Prim(Graph&);
	std::vector<node*> node_list;
	std::vector<edge> edge_list;
	std::vector<std::vector<GEdge>> Adj; // adjacency list
	SqMatrix W;
	int En; // num edges
	int Vn; // num vertices
protected:
	void build(std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			node* v = node_list[i];
			for (int k{ 0 }; k < (n_rows-i); k++) {
				node* u = node_list[k];
				if (m[i][k] != 0) {
					GEdge edge(u, v, m[i][k]);
					Adj[i].push_back(edge);
					Adj[k].push_back(edge);
					edge_list.push_back(edge);
					W(i, k) = m[i][k];
				}
			}
		}
	}
	void build_sparse(std::vector<std::vector<int>>& m) {
		int n_rows = m.size();
		for (int i{ 0 }; i < n_rows; i++) {
			node* v = node_list[i];
			for (int k{ 0 }; k < i; k++) {
				node* u = node_list[k];
				if (m[i][k] != 0) {
					GEdge edge(u, v, m[i][k]);
					Adj[i].push_back(edge);
					Adj[k].push_back(edge);
					edge_list.push_back(edge);
					W(i, k) = m[i][k];
				}
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

	void initializeW(int rows) {
		for (int i{ 0 }; i < rows; i++) {
			for (int j{ 0 }; j < rows; j++) {
				if (i == j) W(i, j) = 0;
				else W(i, j) = MAX_INT;
			}
		}
	}
};

#endif