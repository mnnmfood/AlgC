#ifndef MST_H
#define MST_H

#include<graphs/graph.h>
#include<sets/DisjForest.h>

std::vector<GEdge> Kruskal(UndiGraph G) {
	std::vector<GEdge> edges = G.edge_list;
	std::sort(edges.begin(), edges.end(), [](GEdge x, GEdge y) {return x.w < y.w; });
	return edges;
}

#endif
