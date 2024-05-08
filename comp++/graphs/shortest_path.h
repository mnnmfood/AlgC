#ifndef SHORT_PATH_H
#define SHORT_PATH_H

#include <limits>
#include "graphs/graph.h"

const inline int MAX_INT = std::numeric_limits<int>::max();

void initalize_single(Graph G, GNode* s) {
	for (auto node : G.node_list) {
		node->d = MAX_INT;
		node->pi = -1;
	}
	s->d = 0;
}

void relax(GNode* u, GNode* v, int w) {
	int temp = (u->d == MAX_INT) ? MAX_INT : u->d + w;
	if (v->d > temp) {
		v->d = temp;
		v->pi = u->idx;
	}
}

int Bellman_Ford(Graph G, GNode* s, GNode* d, std::vector<GNode*>& res){
	initalize_single(G, s);
	for (int i{ 0 }; i < G.node_list.size(); i++) {
		for (auto edge : G.edge_list) {
			GNode* u = edge.u;
			GNode* v = edge.v;
			int w = edge.w;
			relax(u, v, w);
		}
	}
	for (auto edge : G.edge_list) {
		GNode* u = edge.u;
		GNode* v = edge.v;
		int w = edge.w;
		if (v->d > (u->d + w)) {
			return 0;
		}
	}
	
	if (d->d < std::numeric_limits<int>::max()) {
		while (d->pi != -1) {
			res.push_back(d);
			d = G.node_list[d->pi];
		}
		res.push_back(s);
	}

	return 1;
}

#endif

