#ifndef MAX_FLOW_H
#ifndef MAX_FLOW_H

#include "graphs/graph.h"

void updateResidualNetwork(Graph& G, Graph& Gr) {
	for (int i{ 0 }; i < G.edge_list.size(); i++) {
		int flow = G.edge_list[i].flow;
		int c = G.edge_list[i].c;
		int u = G.edge_list[i].u->idx;
		int v = G.edge_list[i].v->idx;
		if (flow > 0) {
			Gr.addEdgeDir(v, u, flow, 0);
		}
		if ((c - flow) > 0) {
			Gr.addEdgeDir(u, v, c - flow, 0);
		}
	}
}

void augmentNetwork(Graph& G, Graph& Gr) {
	for (int i{ 0 }; i < Gr.edge_list.size(); i++) {
		int u = Gr.edge_list[i].u;
		int v = Gr.edge_list[i].v;
		int flow = Gr.edge_list[i].flow;
		if (G.isEdge(u, v)) {
		}
	}
}


#endif
