#ifndef FLOW_GRAPH_H
#define FLOW_GRAPH_H


#include <vector>
#include <limits>
#include "stacks_queues/queue.h"
#include "sets/DisjForest.h"
#include "trees/fibonacci_heap.h"
#include "graphs/matrices.h"


struct FNode: public DisjNode<int>, public FBNode<int>
{
	int idx, color, pi, d;
	FNode(int i) : idx{ i }, color{ white }, 
		pi{ -1 }, d{ std::numeric_limits<int>::max() } {}
	void update(int c) { color = c; }
};

struct FEdge
{
	FNode* u, * v;
	int f, c;
	int idx1, idx2;
	FEdge(FNode* u_, FNode* v_, int _c) : u{ u_ }, v{ v_ }, c{ _c }, f{ 0 } {}
};

class FGraph
{
public:
	typedef FNode node_t;
	typedef FEdge edge_t;

	FGraph(int vn, int s, int t) 
			: Vn{ vn }, A{ vn }, A_p{ vn }, source{ s }, sink{ t } {
		for (int i{ 0 }; i < vn; i++) {
			node_list.push_back(new node_t(i));
		}
		Adj.resize(Vn); // network
		Adj_p.resize(Vn); // residual network

		A.setConstant(0);
		A_p.setConstant(0);
	}

	void addEdge(int u, int v, int c=0){
		assert((u < Vn) && "Index exceeded graph size\n");
		FEdge* edge = new edge_t(node_list[u], node_list[v], c);
		edge_list.push_back(edge);
		// add to flow network
		Adj[u].push_back(edge);
		A(u, v) = edge;

		// add to residual network in both directions
		FEdge* edge_res = new edge_t(node_list[u], node_list[v], 0);
		FEdge* edge_res2 = new edge_t(node_list[v], node_list[u], 0);
		Adj_p[u].push_back(edge_res);
		Adj_p[v].push_back(edge_res2);
		A_p(u, v) = edge_res;
		A_p(v, u) = edge_res2;
	}

	int breadth_first(int si, int di, std::vector<FNode*>& res) {
		for (auto node : node_list) node->d = MAX_INT;
		Queue<node_t*> q(Vn);
		node_t* s = node_list[si];
		s->d = 0;
		s->color = gray;
		q.enqueue(s);
		while (!q.isEmpty()) {
			node_t* u = q.dequeue();
			for (int i{ 0 }; i < Adj_p[u->idx].size(); i++) {
				node_t* v = Adj_p[u->idx][i]->v;
				if ((Adj_p[u->idx][i]->c > 0) && (v->color == white)) {
					v->d = u->d + 1;
					v->color = gray;
					v->pi = u->idx;
					q.enqueue(v);
				}
			}
			u->color = black;
		}
		node_t* d = node_list[di];
		if (d->d = MAX_INT) return 0; // if no path found

		while (d->pi != -1) {
			res.push_back(d);
			d = node_list[d->pi];
		}
		res.push_back(d);
		return 1; // if path found
	}
	
	void Ford_Fulkerson() {
		for (auto edge : edge_list) {
			edge->f = 0;
		}
		std::vector<FNode*> res;
		int min_c = MAX_INT;
		while (breadth_first(source, sink, res)) {
			// get capacity of path
			for (auto node : res) {
				FEdge* edge = A_p(node->pi, node->idx);
				if (edge->c <= min_c) {
					min_c = edge->c;
				}
			}
			for (auto node : res) {
				int u = node->pi;
				int v = node->idx;
				// update network 
				if (A(u, v) != 0) {
					edge_t* edge1 = A(node->pi, node->idx);
					edge1->f -= min_c;
				}
				else {
					edge_t* edge1 = A(node->idx, node->pi);
					edge1->f -= min_c;
				}
				// update residual network
				FEdge* edge2 = A_p(node->pi, node->idx);
				edge2->c -= min_c;
			}

		}
	}
	
	int isEdge(int u, int v) {
		return static_cast<int>(A(u, v) != 0);
	}

	std::vector<node_t*> node_list;
	std::vector<edge_t*> edge_list;
	std::vector<std::vector<edge_t*>> Adj; // adjacency list of G
	std::vector<std::vector<edge_t*>> Adj_p; // adjacency list of G'
	SqMatrix<edge_t*> A;
	SqMatrix<edge_t*> A_p;
	int source = 0; 
	int sink = 0; 
	int En; // num edges
	int Vn; // num vertices
};

std::ostream& operator<<(std::ostream& out, const SqMatrix<FEdge*>& A) {
	int rows = A.rows();
	for (int i{ 0 }; i < rows; i++) {
		for (int j{ 0 }; j < rows; j++) {
			FEdge* edge = A(i, j);
			if (edge == 0) out << "0, ";
			else out << edge->f << "/" << edge->c << ", ";
		}
		out << "\n";
	}
	out << "\n";
	return out;
}

#endif
