#ifndef PAIRS_SHORTEST_H
#define PAIRS_SHORTEST_H

#include <algorithm>
#include <limits>
#include "graphs/graph.h"
#include "graphs/matrices.h"


void extend_path(SqMatrix& L, SqMatrix& W, SqMatrix& L_p, SqMatrix& pi) {
	int rows = W.rows();
	for (int i{ 0 }; i < rows; i++) {
		for (int j{ 0 }; j < rows; j++) {
			L_p(i, j) = INT_MAX;
			for (int k{ 0 }; k < rows; k++) {
				int temp = L(i, k) + W(k, j);
				if (temp < L(i, j)) {
					L_p(i, j) = temp;
					pi(i, j) = pi(k, j);
				}
			}
		}
	}
}
 
SqMatrix& slow_all_pairs(SqMatrix& W) {
	int n = W.rows();
	SqMatrix L(n); // min distances L(m-1)
	SqMatrix L_p(n); // min distances L(m)
	L = W;
	SqMatrix pi(n); 
	// initialize predecessor matrix
	for (int i{ 0 }; i < n; i++) {
		for (int j{ 0 }; j < n; j++) {
			if ((i == j) || (W(i, j) == INT_MAX)) pi(i, j) = -1;
			else pi(i, j) = i;
		}
	}
	for (int i{ 0 }; i < n; i++) {
		extend_path(L, W, L_p, pi);
		L = L_p;
	}
	return pi;
}


#endif
