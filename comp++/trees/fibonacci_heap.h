#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <vector>
#include <cmath>

template<typename T>
struct FBNode
{
	typedef FBNode<T> node;

	FBNode() :mark{ false }, deg{ 0 }, left{ 0 }, 
		right{ 0 }, p{ 0 }, c{ 0 } {}
	FBNode(T k) :FBNode() { key = k; }

	void insert_left(node* root){
		if (root == 0) {
			left = right = this;
		}
		else {
			node* temp = root->left;
			root->left = this;
			right = root;
			left = temp;
			temp->right = this;
		}
	}

	void concat(node* root) {
		if (root != 0) {
			node* temp1 = root->left;
			node* temp2 = right;
			root->left = this;
			right = root;
			temp1->right = temp2;
			temp2->left = temp1;
		}
	}

	void remove() {
		if (right != this) { // if list is not empty
			right->left = left;
			left->right = right;
		}
	}

	T key;
	int mark;
	int deg;
	node* left, * right, * p, * c;
};

template<typename T>
class FibHeap
{
public:
	typedef FBNode<T> node;
	FibHeap() : min{ 0 }, n{ 0 }, deg{ 0 } {}
	node* insert(T k) {
		node* p = new node(k);
		p->insert_left(min);
		if ((min == 0) || (p->key < min->key)){
			min = p;
		}
		deg++;
		n++;
		return p;
	}
	
	// Remove y from root list and make it a child of x
	void link(node* y, node* x) {
		y->remove();
		y->insert_left(x->c);
		if (x->c == 0) {
			x->c = y;
		}
		y->p = x;
		x->deg++;
		y->mark = false;
	}
	
	void Consolidate() {
		int D_n = static_cast<int>(floor(log2(n)));
		std::vector<node*> A(D_n + 1);
		for (int i{ 0 }; i < D_n; i++) {
			A[i] = 0;
		}
		node* x = min;
		for (int i{ 0 }; i < deg; i++) {
			int d = x->deg;
			while (A[d] != 0) {
				node* y = A[d];
				if (y->key < x->key) { // exchange x and y pointers
					// so that x remains a root
					node* temp = y;
					y = x;
					x = temp;
				}
				link(y, x);
				A[d] = 0;
				d++;
			}
			A[d] = x;
			x = x->right;
		}
		// Reconstruct root list from A
		min = 0;
		deg = 0;
		for (int i{ 0 }; i <= D_n; i++) {
			if (A[i] != 0) {
				A[i]->insert_left(min);
				deg++;
				if ((min == 0) || (A[i]->key < min->key)) {
					min = A[i];
				}
				A[i] = 0;
			}
		}
	}
	
	node* extract_min() {
		assert((deg > 0) && "Queue is empty");
		node* z = min;
		if (z != 0) {
			node* c = z->c;
			// add children to root list
			for (int i{ 0 }; i < z->deg; i++) {
				node* temp = c->right;
				c->insert_left(z);
				c->p = 0;
				c = temp;
				deg++;
			}
			z->remove();
			deg--;
			if (z == z->right) {
				min = 0;
			}
			else {
				min = z->right;
				Consolidate();
			}
			n--;
		}
		return z;
	}

	void cut(node* x, node* y) {
		x->remove(); // remove it from y child list
		if (y->c == x) y->c = x->left;
		y->deg--;
		x->insert_left(min); // add it to root list
		deg++;
		x->p = 0;
		x->mark = 0;
	}

	void cascading_cut(node* y) {
		node* z = y->p;
		if (z != 0) {
			if (y->mark == 0) {
				y->mark = 1;
			}
			else {
				cut(y, z);
				cascading_cut(z);
			}
		}
	}

	void decrease_key(node* x, T k) {
		assert((k < x->key) && "New key is greater than current\n");
		x->key = k;
		node* y = x->p;
		if ((y!=0) && (y->key > x->key)){
			cut(x, y);
			cascading_cut(y);
		}
		if (x->key < min->key) min = x;
	}

	// Tree traversal
	void inorder() {
		node* c = min;
		for (int i{ 0 }; i < deg; i++) {
			std::cout << "Heap " << i << ": ";
			std::cout << c->key << ", ";
			inorder(c);
			c = c->right;
			std::cout << "\n";
		}
	}
	void inorder(node* p) {
		node* c = p->c;
		for (int i{ 0 }; i < p->deg; i++) {
			inorder(c);
			std::cout << c->key << ", ";
			c = c->right;
		}
	}
	
	int size() { return n; }
	friend FibHeap<T> merge(FibHeap<T> H1, FibHeap<T> H2);
private:
	int n; // total number of nodes
	node* min; // ptr to root list
	int deg; // number of nodes in root list
};

template<typename T>
FibHeap<T> merge(FibHeap<T> H1, FibHeap<T> H2) {
	FibHeap<T> H;
	H.min = H1.min;
	H.min->concat(H2.min);
	if ((H1.min == 0) || ((H2.min != 0) && (H1.min > H2.min))) {
		H.min = H2.min;
	}
	H.n = H1.n + H2.n;
	return H;
}


#endif
