#ifndef DISJ_TREE_H
#define DISJ_TREE_H

#include <vector>
#include <algorithm>

template<typename T>
struct DisjNode
{
	typedef DisjNode<T> node;
	T key;
	int rank;
	node* p;
	DisjNode(T k) : key{ k }, rank{ 0 } { p = this; }
	DisjNode(T k, node* parent) : key{ k }, rank{ 0 }, p { parent } {}
};

template<typename T>
class DisjForest
{
public:
	typedef DisjNode<T> node;
	DisjForest(){}
	DisjForest(node* x) {
		Make_set(x);
	}
	
	void Make_set(node* x) {
		roots.push_back(x);
	}
	// find root with path compression
	node* Find_set(node* x) { 
		if (x->p != x) {
			x->p = Find_set(x->p);
		}
		return x->p;
	}

	void Link(node* x, node* y) {
		if (x->rank > y->rank) {
			roots.erase(std::remove(roots.begin(), roots.end(), y));
			y->p = x;
		}
		else {
			if (x->rank == y->rank) {
				roots.erase(std::remove(roots.begin(), roots.end(), y));
				y->p = x;
				x->rank++;
			}
			else {
				roots.erase(std::remove(roots.begin(), roots.end(), x));
				x->p = y;
			}
		}
	}

	void Union(node* x, node* y) {
		Link(Find_set(x), Find_set(y));
	}
	
	std::vector<node*> roots;
};

#endif
