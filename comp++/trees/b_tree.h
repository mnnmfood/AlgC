#ifndef B_TREE_H
#define B_TREE_H

template<typename T, size_t t>
class BNode
{
	typedef BNode<T, t> node;
public:
	BNode() :n{ 0 }, leaf{ 1 } {}
	
	node* c[2 * t]; // array of pointers to children
	T key[2 * t - 1];
	int n = 0;
	int leaf = 1;
};

template<typename T, size_t t>
class BTree
{
public:
	typedef BNode<T, t> node;
	typedef std::pair<node*, int> return_t;
	BTree() { root = new node(); }

	return_t search(node* x, T k) {
		int i = 0;
		while ((x->n > 0) && (k > x->key[i])) {
			i++;
		}
		if ((i < x->n) && (x->key[i] == k)) {
			return return_t(x, i);
		}
		else if (x->leaf) return return_t(nullptr, 0);
		else {
			return search(x->c[i], k);
		}
	}
	
	// Helper function for insertion
	void split_child(node* x, int ind) {
		node* z = new node();
		node* y = x->c[ind];
		z->leaf = y->leaf;
		z->n = t - 1;
		for (int i{ 0 }; i < t - 1; i++) { 
			z->key[i] = y->key[i + t];
		}
		if ((y->leaf)==0){
			for (int i{0}; i < t; i++) {
				z->c[i] = y->c[i + t];
			}
		}
		y->n = t - 1;
		for (int i{ x->n }; i > ind; i--) {
			x->key[i + 1] = x->key[i];
		}
		for (int i{ x->n + 1 }; i > ind + 1; i--) {
			x->c[i + 1] = x->c[i];
		}
		x->key[ind] = y->key[t-1];
		x->c[ind + 1] = z;
		x->n++;
	}
	// Insertion: requires a single pass down the tree and each
	// node requires at most t comparisons: O(th) = O(tlg(n))
	void insert(T k) {
		node* r = root;
		if ((r->n) == 2 * t - 1) { // if root is full
			// split root
			node* s = new node();
			root = s;
			s->n = 0;
			s->c[0] = r;
			s->leaf = 0;
			split_child(s, 0);
			insert_nonfull(s, k);
		}
		else {
			insert_nonfull(r, k);
		}
	}
	void insert_nonfull(node* x, T k) {
		int i = x->n;
		if (x->leaf) {
			while (i >= 0 && (k < x->key[i-1])) {
				x->key[i + 1] = x->key[i];
				i--;
			}
			x->key[i] = k;
			x->n++;
		}
		else {
			while (i > 0 && (k < x->key[i-1])) {
				--i;
			}
			node* c = x->c[i];
			if ((c->n) == 2 * t - 1) {
				split_child(x, i);
				if (k > x->key[i]) i++;
			}
			insert_nonfull(x->c[i], k);
		}
	}

	// Helper functions for deletion
	node* move_to_parent(node* x, int i, node* c) {
		node* temp;
		if (x->key[i] > c->key[0]) { // if predecessor
			int n = c->n;
			x->key[i] = c->key[n - 1];
			temp = c->c[n];
			c->n--;
		}
		else { // if successor
			x->key[i] = c->key[0];
			// move keys to the left
			for (int ind{ 0 }; ind < c->n-1; ind++) {
				c->key[ind] = c->key[ind + 1];
			}
			temp = c->c[0];
			// move children to the left
			for (int ind{ 0 }; ind < c->n; ind++) {
				c->c[ind] = c->c[ind + 1];
			}
			c->n--;
		}
		return temp;
	}
	void move_to_child(node* x, int i, node* c) {
		if (x->key[i] > c->key[0]) { // if predecessor
			int n = c->n;
			c->key[n] = x->key[i];
			c->n++;
		}
		else { // if successor
			c->key[i] = c->key[0];
			c->n++;
		}
	}

	void merge_children(node* x, int i){
		node* cl = x->c[i];
		node* cr = x->c[i+1];
		int nl = cl->n;
	
		cl->key[nl] = x->key[i];
		cl->n++;
		nl++;
		// move parent keys to the left
		for (int ind{ i }; ind < x->n-1; ind++) {
			x->key[ind] = x->key[ind + 1];
		}
		x->n--;
		// move parent children to the left
		for (int ind{ i+1 }; ind < x->n; ind++) {
			x->c[ind] = x->c[ind + 1];
		}
		// move right child to left child
		for (int ind{ 0 }; ind < cr->n; ind++) {
			cl->key[ind + nl] = cr->key[ind];
			cl->n++;
		}
		for (int ind{ 0 }; ind < cr->n+1; ind++) {
			cl->c[ind + nl] = cr->c[ind];
		}
	}
	
	void del(node* x, T k) {
		int i = 0;
		while ((i < x->n) && (k > x->key[i])) {
			i++;
		}
		if (x->leaf) { // case 1
			if (x->key[i] == k) {
				for (int ind{ i }; i < x->n-1; i++) {
					x->key[i] = x->key[i + 1];
				}
				x->n--;
			}
		}
		else if (x->key[i] == k) { // case 2
			int nl = x->c[i]->n;
			int nr = x->c[i+1]->n;
			if (nl > t - 1) { // case 2.a
				T kp = x->c[i]->key[nl-1];
				del(x->c[i], kp);
				x->key[i] = kp;
			}
			else if (nr > t - 1) { // case 2.b
				T kp = x->c[i + 1]->key[0];
				del(x->c[i + 1], kp);
				x->key[i] = kp;
			}
			else { // case 2.c
				merge_children(x, i);
				del(x->c[i], k);
			}
		}
		else { // case 3
			node* xp = x->c[i];
			if (xp->n > t - 1) {
			}
			else if (x->c[i + 1]->n > t - 1) { // case 3.a.1
				node* xpr = x->c[i + 1];
				move_to_child(x, i, xp);
				node* temp = move_to_parent(x, i, xpr);
				// move orphaned node to right child
				xp->c[xp->n] = temp;
			}
			else if (x->c[i - 1]->n > t - 1) { // case 3.a.2
				node* xpl = x->c[i - 1];
				move_to_child(x, i-1, xp);
				node* temp = move_to_parent(x, i - 1, xpl);
				xp->c[0] = temp;
			}
			else {
				merge_children(x, i);
			}
			del(xp, k);
		}
	}
	
	// Traverse tree
	void inorder(node* p) {
		if ((p->leaf) == 0){
			for (int i{ 0 }; i < p->n; i++) {
				inorder(p->c[i]);
				std::cout << p->key[i] << ", ";
			}
			inorder(p->c[p->n]);
		}
		else {
			std::cout << "\nleaf: ";
			for (int i{ 0 }; i < p->n; i++) {
				std::cout << p->key[i] << ", ";
			}
			std::cout << "\n";
		}
	}



	node* root;
};


#endif
