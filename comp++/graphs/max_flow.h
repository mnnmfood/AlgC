#ifndef FLOW_GRAPH_H
#define FLOW_GRAPH_H


#include <vector>
#include <list>
#include <limits>
#include "stacks_queues/queue.h"
#include "sets/DisjForest.h"
#include "trees/fibonacci_heap.h"
#include "graphs/matrices.h"


struct FNode: public DisjNode<int>, public FBNode<int>
{
	typedef std::list<FNode*>::iterator it_t;
	int idx, color, pi, d;
	int h, e; // height and overflow for push-relabel 
	it_t current; // for relabel-to-front
	std::list<FNode*> N; // for relabel-to-front

	FNode(int i) : idx{ i }, color{ white }, 
		pi{ -1 }, d{ std::numeric_limits<int>::max() } {}
	void update(int c) { color = c; }
	it_t head() { return N.begin();}
	int nil(it_t v) { return v == N.end(); }
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
	typedef std::list<FNode*>::iterator it_t;

	FGraph(int vn, int s, int t) 
			: Vn{ vn }, A{ vn }, A_p{ vn }, source{ s }, sink{ t } {
		for (int i{ 0 }; i < vn; i++) {
			node_t* node = new node_t(i);
			node_list.push_back(node);
			if ((i != s) && (i != t)) L.push_back(node);
		}
		Adj.resize(Vn); // network
		Adj_p.resize(Vn); // residual network

		A.setConstant(0);
		A_p.setConstant(0);
	}

	void addEdge(int u, int v, int c=0){
		assert((u < Vn) && "Index exceeded graph size\n");
		node_t* u_n = node_list[u];
		node_t* v_n = node_list[v];
		FEdge* edge = new edge_t(u_n, v_n, c);
		edge_list.push_back(edge);
		// add to flow network
		Adj[u].push_back(edge);
		A(u, v) = edge;
		// add to residual network in both directions
		FEdge* edge_res = new edge_t(u_n, v_n, c);
		FEdge* edge_res2 = new edge_t(v_n, u_n, 0);
		Adj_p[u].push_back(edge_res);
		Adj_p[v].push_back(edge_res2);
		A_p(u, v) = edge_res;
		A_p(v, u) = edge_res2;
		// add to neighbour lists
		u_n->N.push_back(v_n);
		v_n->N.push_back(u_n);
	}
	
	void updateFlow(node_t* u, node_t*v, int delta_f) {
		int ui = u->idx;
		int vi = v->idx;
		// update network 
		if(isEdge(ui, vi)){
			edge_t* edge = A(ui, vi);
			edge->f += delta_f;
		}
		else {
			edge_t* edge = A(vi, ui);
			edge->f -= delta_f;
		}
		// update residual network
		FEdge* edge_res1 = A_p(ui, vi);
		FEdge* edge_res2= A_p(vi, ui);
		edge_res1->c -= delta_f;
		edge_res2->c += delta_f;
	}
	// Ford Fulkerson / Edmonds-Karp 
	int breadth_first(int si, int di, std::vector<FNode*>& res) {
		for (auto node : node_list) {
			node->d = MAX_INT;
			node->color = white;
		}
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
		if (d->d == MAX_INT) return 0; // if no path found

		while (d->pi != -1) {
			res.push_back(d);
			d = node_list[d->pi];
		}
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
				updateFlow(node_list[node->pi], node, min_c);
			}
			res.resize(0);
		}
	}

	// Push-relabel 
	void Initialize_preflow() {
		for (auto node : node_list) {
			node->h = node->e = 0;
		}
		for (auto edge : edge_list) {
			edge->f = 0;
			A_p(edge->u->idx, edge->v->idx)->c = edge->c;
			A_p(edge->v->idx, edge->u->idx)->c = 0;
		}
		node_list[source]->h = Vn;
		for (auto edge : Adj[source]) {
			edge->f = edge->c;
			node_t* s = edge->u;
			node_t* v = edge->v;
			v->e = edge->c;
			s->e -= edge->c;
			A_p(s->idx, v->idx)->c = 0;
			A_p(v->idx, s->idx)->c = edge->f;
		}
	}

	void Push(edge_t* edge) {
		node_t* u = edge->u;
		node_t* v = edge->v;
		int delta_f = std::min(edge->c, u->e);
		updateFlow(u, v, delta_f);
		//if(isEdge(u->idx, v->idx)) edge->f += delta_f;
		//else edge->f -= delta_f;
		u->e -= delta_f;
		v->e += delta_f;
	}

	void Relabel(node_t* u) {
		int min_h = MAX_INT;
		for (auto edge : Adj_p[u->idx]) {
			if (edge->c > 0) { // edge is in Ef only if its capacity is > 0
				int h = edge->v->h;
				min_h = h < min_h ? h : min_h;
			}
		}
		u->h = min_h + 1;
	}

	void Discharge(node_t* u) {
		while (u->e > 0) {
			it_t v_it = u->current;
			if (u->nil(v_it)) {
				Relabel(u);
				u->current = u->head();
			}
			else if ((A_p(u->idx, (*v_it)->idx)->c > 0) && (u->h == (*v_it)->h + 1)) {
				node_t* v = *v_it;
				edge_t* edge = A_p(u->idx, v->idx);
				Push(edge);
			}
			else {
				v_it++;
				u->current = v_it;
			}
		}
	}
	
	void move_to_front(std::list<node_t*>& l, it_t& pos) {
		it_t next = std::next(pos);
		it_t begin = l.begin();
		l.splice(next, l, begin, pos);
	}

	void Relabel_to_front() {
		Initialize_preflow();
		for (auto node : L) {
			node->current = node->N.begin();
		}
		it_t u_it = L.begin();
		while (u_it != L.end()) {
			node_t* u = *u_it;
			int old_h = u->h;
			Discharge(u);
			if (u->h > old_h) {
				move_to_front(L, u_it);
			}
			u_it++;
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
	std::list<node_t*> L;
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
