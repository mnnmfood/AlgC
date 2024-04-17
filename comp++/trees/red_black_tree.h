#ifndef RB_TREE
#define RB_TREE

enum color {RED, BLACK};

template<typename T>
class RBNode
{
	typedef RBNode<T> node;
public:
	RBNode() {}
	RBNode(T& val) :key { val } {}
	RBNode(node* le, node* ri, node*pa) 
		: left{ le }, right{ ri }, parent{ pa } {}
	
	node* left = 0, *right = 0, *parent = 0;
	int color = BLACK;
	T key;
};

template<typename T>
class RBTree
{
public:
	typedef RBNode<T> node;
	RBTree() { nil = new node(); root = nil; }

	// Rotations. O(1)
	void left_rotate(node* x) {
		node* y = x->right;
		// left child of y becomes right child of x
		x->right = y->left;
		if (y->left != nil) { y->left->parent = x; }
		// parent of x becomes parent of y
		y->parent = x->parent;
		if (x->parent == nil) { root = y; }
		// child of parent of x becomes y
		else if (x = x->parent->left) { x->parent->left = y; }
		else { x->parent->right = y; }
		// x becomes left child of y
		y->left = x;
		x->parent = y;
	}
	void right_rotate(node* y) {
		node* x = y->left;
		y->left = x->right;
		if (x->right != nil) { x->right->parent = y; }
		x->parent = y->parent;
		if (y->parent == nil) { root = x; }
		else if (y == y->parent->left) { y->parent->left = x; }
		else { y->parent->right = x; }
		// y becomes right child of x
		x->right = y;
		y->parent = x;
	}
	
	// --- Insertion O(logn)
	void insert(T& val) {
		node* z = new node(val);
		node* y = nil;
		node* x = root;
		while (x != nil) {
			y = x;
			if (val < x->key) { x = x->left; }
			else { x = x->right; }
		}
		z->parent = y;
		if (y == nil) { root = z; }
		else if (val < y->key) { y->left = z; }
		else { y->right = z; }
		z->color = RED;
		z->left = nil;
		z->right = nil;
		insert_fixup(z);
	}
	void insert_fixup(node* z) {
		while (z->parent->color == RED) {
			if (z->parent == z->parent->parent->left) {
				node* y = z->parent->parent->right;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					right_rotate(z);
				}
			}
			else {
				node* y = z->parent->parent->left;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						right_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					left_rotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	// --- Deletion O(logn)
	// Very similar to deletion in ordinary binary tree. 2 differences:
	//		1-We keep track of 2 node:
	//			-y==node that is deleted or changed in the tree
	//			-x==node that replaces y
	//		2-At the end we call fixup to reestablish red-black properties
	//			with the color of the original removed/moved node y
	//			and the color of the replacement node x
	void transplant(node* u, node* v) {
		if (u->parent == nil) { root = v; }
		else if (u == u->parent->left) { u->parent->left = v; }
		else if (u == u->parent->right) { u->parent->right = v; }
		v->parent = u->parent; 
	}
	void tdelete(node* z) {
		int color_orig = z->color;
		node* x = 0;
		node* y = z;
		if (z->left == nil) { 
			x = z->right;
			transplant(z, z->right); 
		}
		else if (z->right == nil) { 
			x = z->left;
			transplant(z, z->left); 
		}
		else {
			y = min(z->right);
			color_orig = y->color;
			x = y->right;
			if (y->parent == z) { x->parent = y; }
			else {
				// 3.2
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			// 3.1
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (color_orig == BLACK)
			delete_fixup(x);
		delete z;
	}

	void delete_fixup(node* x) {
		while (x != root && x->color != BLACK) {
			if (x == x->parent->left) {
				node* w = x->parent->right;
				if (w->color == RED) { // Case 1
					x->parent->color = RED;
					w->color = BLACK;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) { // Case 2
					w->color = RED;
					x = x->parent;
				}
				else if (w->right->color == BLACK) { // Case 3
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(w);
					w = w->left;
				}
				else{ // Case 4 
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					left_rotate(x->parent);
				}

			}
			else {
				node* w = x->parent->left;
				if (w->color == RED) { // Case 1
					x->parent->color = RED;
					w->color = BLACK;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2
					w->color = RED;
					x = x->parent;
				}
				else if (w->left->color == BLACK) { // Case 3
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(w);
					w = w->right;
				}
				else{ // Case 4 
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					right_rotate(x->parent);
				}
			}
		}
	}

	// --- Minimum and maximum	O(h)
	node* min(node* p) {
		while (p->left != nil) {
			p = p->left;
		}
		return p;
	}
	node* max(node* p) {
		while (p->right != nil) {
			p = p->right;
		}
		return p;
	}


	// --- Successor and Predecessor O(h)
	// Successor: the node with the smallest key greater than p	
	// Predecessor: the node with the highest key smaller than p
	node* successor(node* p) {
		if (p->right != nil) {
			return min(p->right);
		}
		node* temp = p->parent;
		while (temp != 0 && p == temp->right) {
			p = temp;
			temp = p->parent;
		}
		return temp;
	}
	node* predecessor(node* p) {
		if (p->left != nil) {
			return max(p->left);
		}
		node* temp = p->parent;
		while (temp != nil && p == temp->left) {
			p = temp;
			temp = p->parent;
		}
		return temp;
	}

	// -- Tree search 
	// O(h) where h==height of tree 
	// If the tree is balanced h = lg(n) so 
	// O(h) == O(logn)
	node* recursive_search(node* p, T& val) {
		if (p == nil || p->key == val) {
			return p;
		}
		if (p->key > val) return recursive_search(p->left, val);
		else return recursive_search(p->right, val);
	}
	node* iter_search(T& val) {
		node* p = root;
		while (p != nil || p->key != val) {
			if (p->key > val) p = p->left;
			else p = p->right;
		}
		return p;
	}

	// Inorder: visit all the way left, print, then right. 
	void inorder(node* p) {
		if (p != nil) {
			inorder(p->left);
			// visit node
			std::cout << p->key << "-";
			std::cout << ((p->color==RED) ? "Red": "Black") << ", ";
			inorder(p->right);
		}
	}

	node* nil; // used as sentinel value. Black
	node* root = 0;
};

#endif
