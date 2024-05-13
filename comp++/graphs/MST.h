#ifndef MST_H
#define MST_H

#include <limits>
#include<graphs/graph.h>
#include<sets/DisjForest.h>
#include "trees/fibonacci_heap.h"

std::vector<GEdge> Kruskal(Graph& G) {
	std::vector<GEdge> A;
	std::vector<GEdge> edges = G.edge_list;
	std::vector<GNode*> nodes = G.node_list;
	std::sort(edges.begin(), edges.end(), [](GEdge x, GEdge y) {return x.w < y.w; });

	DisjForest<int> sets;
	for (int i{ 0 }; i < nodes.size(); i++) {
		sets.Make_set(nodes[i]);
	}
	for (auto edge : edges) {
		if (sets.Find_set(edge.u) != sets.Find_set(edge.v)) {
			A.push_back(edge);
			sets.Union(edge.u, edge.v);
		}
	}
	return A;
}

void debugCb(int i, FBNode<int>* c) {
	GNode* temp = static_cast<GNode*>(c);
	std::cout << temp->idx << ", ";
}

int debugCb2(int i, FBNode<int>* c) {
	return static_cast<GNode*>(c)->idx;
}

std::vector<GEdge> Prim(Graph& G) {
	FibHeap<int> Q;
	std::vector<GNode*> nodes = G.node_list;
	std::vector<int> isinQ;

	nodes[0]->pi = -1;
	nodes[0]->key = 0;
	isinQ.push_back(1);
	Q.insert(nodes[0]);
	for (size_t i{ nodes.size() - 1}; i > 0; i--) {
		nodes[i]->pi = -1;
		nodes[i]->key = std::numeric_limits<int>::max();
		Q.insert(nodes[i]);
		isinQ.push_back(1);
	}
	while (!Q.isEmpty()) {
		GNode* u = static_cast<GNode*>(Q.extract_min());
		isinQ[u->idx] = 0;
		for (int i{ 0 }; i < G.Adj[u->idx].size(); i++) {
			GNode* v = G.Adj[u->idx][i].v; // for each neighbor
			int w = G.Adj[u->idx][i].w;
			if (isinQ[v->idx] && (w < v->key)) {
				v->pi = u->idx;
				Q.decrease_key(v, w);
			}
		}
	}
	std::vector<GEdge> res;
	for (int i{ 0 }; i < nodes.size(); i++) {
		GNode* u = nodes[i];
		if (u->pi != -1) {
			GNode* v = nodes[u->pi];
			res.push_back(GEdge(u, v, 0));
		}
	}
	return res;
}

#endif
