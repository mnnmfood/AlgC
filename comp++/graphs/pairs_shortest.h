#ifndef PAIRS_SHORTEST_H
#define PAIRS_SHORTEST_H

#include <algorithm>
#include <limits>
#include "graphs/graph.h"
#include "graphs/matrices.h"


void extend_path(const SqMatrix& L, const SqMatrix& W, SqMatrix& L_p){
	int rows = W.rows();
	for (int i{ 0 }; i < rows; i++) {
		for (int j{ 0 }; j < rows; j++) {
			L_p(i, j) = INT_MAX;
			for (int k{ 0 }; k < rows; k++) {
				int temp = ((W(k, j) == MAX_INT) || (L(i, k) == MAX_INT)) 
					? MAX_INT : L(i, k) + W(k, j); // prevent overflow
				if (temp < L_p(i, j)) {
					L_p(i, j) = temp;
				}
			}
		}
	}
}
 
void slow_all_pairs(const SqMatrix& W, SqMatrix& L_p){
	int n = W.rows();
	SqMatrix L(n); 
	L = W;
	for (int i{ 0 }; i < n; i++) {
		extend_path(L, W, L_p);
		L = L_p;
	}
}

void Floyd_Warshall(const SqMatrix& W, SqMatrix& D_p, SqMatrix& pi_p) {
	int n = W.rows();
	SqMatrix D(n); // min distances L(m-1)
	D = W;
	SqMatrix pi(n);
	// initialize predecessor matrix
	for (int i{ 0 }; i < n; i++) {
		for (int j{ 0 }; j < n; j++) {
			if ((i == j) || (W(i, j) == INT_MAX)) pi(i, j) = -1;
			else pi(i, j) = i;
		}
	}
	for (int k{ 0 }; k < n; k++) {
		for (int i{ 0 }; i < n; i++) {
			for (int j{ 0 }; j < n; j++) {
				int temp = ((D(k, j) == MAX_INT) || (D(i, k) == MAX_INT)) 
					? MAX_INT : D(i, k) + D(k, j); // prevent overflow
				if (temp < D(i, j)) {
					D_p(i, j) = temp;
					pi_p(i, j) = pi(k, j);
				}
				else {
					D_p(i, j) = D(i, j);
					pi_p(i, j) = pi(i, j);
				}
			}
		}
		D = D_p;
		pi = pi_p;
	}
}

void TransitiveClosure(Graph& G, SqMatrix& T_p) {
	int n = G.Vn;
	SqMatrix& W = G.W;
	SqMatrix T(n);
	for (int i{ 0 }; i < n; i++) {
		for (int j{ 0 }; j < n; j++) {
			if ((i == j) || (W(i, j)<MAX_INT)){
				T(i, j) = 1;
			}
			else {
				T(i, j) = 0;
			}
		}
	}
	for (int k{ 0 }; k < n; k++) {
		for (int i{ 0 }; i < n; i++) {
			for (int j{ 0 }; j < n; j++) {
				T_p(i, j) = T(i, j) | (T(i, k) & T(k, j));
			}
		}
		T = T_p;
	}
}

#endif
