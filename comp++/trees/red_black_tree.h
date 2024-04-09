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
	RBTree() { nil = new node(); }

	// Rotations. O(1)
	void left_rotate(node* x) {
		node* y = x->right;
		// left child of y becomes right child of x
		x->right = y->left;
		if (y->left != nil) { y->left->parent = x; }
		// parent if x becomes parent of y
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
			if (val < x) { x = x->left; }
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

	node* nil; // used as sentinel value. Black
	node* root;
};

#endif
